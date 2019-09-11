# Handler综述
Handler提供了Android系统里面的消息处理机制，包含Handler、Looper、MessageQueue、Message。
Handler为用户处理Message提供了界面，Looper实现了消息的驱动，MessageQueue和Message提供了消息的基本结构。

# Handler机制详述
## Message
首先看Message基本结构：
```Java
public final class Message implements Parcelable {
    public int what;
    public int arg1; 
    public int arg2;
    public Object obj;
    /*package*/ Handler target;
    /*package*/ Runnable callback;
 
    /**
     * Return a new Message instance from the global pool. Allows us to
     * avoid allocating new objects in many cases.
     */
    public static Message obtain() {
        synchronized (sPoolSync) {
            if (sPool != null) {
                Message m = sPool;
                sPool = m.next;
                m.next = null;
                m.flags = 0; // clear in-use flag
                sPoolSize--;
                return m;
            }
        }
        return new Message();
    }
 
    /** Constructor (but the preferred way to get a Message is to call {@link #obtain() Message.obtain()}).
    */
    public Message() {
    }
}
```
看到这个类的前四个属性，大家应该很熟悉，就是我们使用Handler时经常用到的那几个属性。用来在传递我们特定的信息。其次我们还可以总结出以下信息：
- Message 实现了Parcelable 接口，也就是说实现了序列化，这就说明Message可以在不同进程之间传递。
- 包含一个名为target的Handler 对象
- 包含一个名为callback的Runnable 对象
- 使用obtain 方法可以从消息池中获取Message的实例，也是推荐大家使用的方法，而不是直接调用构造方法。

## MessageQueue
顾名思义，MessageQueue就是一个Message组成的队列，先看其构造函数：
```Java
MessageQueue(boolean quitAllowed) {
    mQuitAllowed = quitAllowed;
    mPtr = nativeInit();
}
```
传入一个bool变量，来决定队列是否可以终止，保存在成员变量mQuitAllowed中；另外使用nativeInit初始化了一个long类型成员mPtr。  
再看另一个方法next():

```Java
Message next() {
    // Return here if the message loop has already quit and been disposed.
    // This can happen if the application tries to restart a looper after quit
    // which is not supported.
    final long ptr = mPtr;
    if (ptr == 0) {
        return null;
    }
	……
}
```
比较长没有截完，主要功能就是Message出队列。其实还有一个对应的方法enqueueMessage实现了进队列的功能，这个后面还会再讲到。

## Looper
Looper主要实现了消息的驱动，MessageQueue也是由它创建的。对于Looper主要关注两个函数，prepare()和loop()。

- Looper-prepare():  
```Java
public static void prepare() {
    prepare(true);
}

private static void prepare(boolean quitAllowed) {
    if (sThreadLocal.get() != null) {
        throw new RuntimeException("Only one Looper may be created per thread");
    }
    sThreadLocal.set(new Looper(quitAllowed));
}
```
可以看到prepare是一个静态方法，主要功能就是创建Looper实例，并将其设置给线程变量sThreadLocal。  
注意一个线程多次调用此函数会抛出异常，实际上这样也就确保了每个线程只有一个Looper实例。

- Looper-loop():
```Java
public static void loop() {
    final Looper me = myLooper();
    if (me == null) {
        throw new RuntimeException("No Looper; Looper.prepare() wasn't called on this thread.");
    }
    final MessageQueue queue = me.mQueue;
    for (;;) {
        Message msg = queue.next(); // might block
        if (msg == null) {
            // No message indicates that the message queue is quitting.
            return;
        }
        msg.target.dispatchMessage(msg);
        msg.recycleUnchecked();
    }
}
/**
 * Return the Looper object associated with the current thread.  Returns
 * null if the calling thread is not associated with a Looper.
 */
public static @Nullable Looper myLooper() {
    return sThreadLocal.get();
}
```
loop是个死循环，功能就是不停的从消息队列中取出消息交由msg.target.dispatchMessage处理。Message定义里面可以看到，这里msg.target实际就是Handler。

## Handler
先从Looper里面使用过的函数dispatchMessage看起：
```Java
public void dispatchMessage(Message msg) {
    if (msg.callback != null) {
        handleCallback(msg);
    } else {
        if (mCallback != null) {
            if (mCallback.handleMessage(msg)) {
                return;
            }
        }
        handleMessage(msg);
    }
}
public Handler() {
    this(null, false);
}
public Handler(Callback callback, boolean async) {
    if (FIND_POTENTIAL_LEAKS) {
        final Class<? extends Handler> klass = getClass();
        if ((klass.isAnonymousClass() || klass.isMemberClass() || klass.isLocalClass()) &&
                (klass.getModifiers() & Modifier.STATIC) == 0) {
            Log.w(TAG, "The following Handler class should be static or leaks might occur: " +
                klass.getCanonicalName());
        }
    }

    mLooper = Looper.myLooper();
    if (mLooper == null) {
        throw new RuntimeException(
            "Can't create handler inside thread that has not called Looper.prepare()");
    }
    mQueue = mLooper.mQueue;
    mCallback = callback;
    mAsynchronous = async;
}
```
容易看出实际处理消息的方法为Handler的handleCallback或handlerMessage方法，构造时传入了Callback对象的情况下消息会交由Callback的handleMessage处理。

Handler中处理消息的函数如下：
```Java
private static void handleCallback(Message message) {
    message.callback.run();
}
public void handleMessage(Message msg) {
}
```
handleCallback实际就是调用Message的callback成员的run方法，而handleMessage是个空实现，需要我们自己重写此方法，此函数就是用户处理消息的界面。

在Handler构造中可以看出，它组合了一个Looper对象，Handler也正是使用此对象来驱动消息。
再看Handler中消息驱动相关函数：
```Java
public final boolean postDelayed(Runnable r, long delayMillis)
{
    return sendMessageDelayed(getPostMessage(r), delayMillis);
}
 
private static Message getPostMessage(Runnable r) {
    Message m = Message.obtain();
    m.callback = r;
    return m;
}

//所有sendMessage和postMessage都会调用到这里
public boolean sendMessageAtTime(Message msg, long uptimeMillis) {
    MessageQueue queue = mQueue;
    if (queue == null) {
        RuntimeException e = new RuntimeException(
                this + " sendMessageAtTime() called with no mQueue");
        Log.w("Looper", e.getMessage(), e);
        return false;
    }
    return enqueueMessage(queue, msg, uptimeMillis);
}

private boolean enqueueMessage(MessageQueue queue, Message msg, long uptimeMillis) {
    msg.target = this;
    if (mAsynchronous) {
        msg.setAsynchronous(true);
    }
    return queue.enqueueMessage(msg, uptimeMillis);
}
```
顺着调用关系发现会调用到MessageQueue的enqueueMessage函数，前面已经说过这是一个消息进消息队列的函数。
```Java
boolean enqueueMessage(Message msg, long when) {
	if (msg.target == null) {
	    throw new IllegalArgumentException("Message must have a target.");
	}
	if (msg.isInUse()) {
	    throw new IllegalStateException(msg + " This message is already in use.");
	}

	synchronized (this) {
	    if (mQuitting) {
	        IllegalStateException e = new IllegalStateException(
	                msg.target + " sending message to a Handler on a dead thread");
	        Log.w(TAG, e.getMessage(), e);
	        msg.recycle();
	        return false;
	    }

	    msg.markInUse();
	    msg.when = when;
	    Message p = mMessages;
	    boolean needWake;
	    if (p == null || when == 0 || when < p.when) {
	        // New head, wake up the event queue if blocked.
	        msg.next = p;
	        mMessages = msg;
	        needWake = mBlocked;
	    } else {
	        // Inserted within the middle of the queue.  Usually we don't have to wake
	        // up the event queue unless there is a barrier at the head of the queue
	        // and the message is the earliest asynchronous message in the queue.
	        needWake = mBlocked && p.target == null && msg.isAsynchronous();
	        Message prev;
	        for (;;) {
	            prev = p;
	            p = p.next;
	            if (p == null || when < p.when) {
	                break;
	            }
	            if (needWake && p.isAsynchronous()) {
	                needWake = false;
	            }
	        }
	        msg.next = p; // invariant: p == prev.next
	        prev.next = msg;
	    }

	    // We can assume mPtr != 0 because mQuitting is false.
	    if (needWake) {
	        nativeWake(mPtr);
	    }
	}
	return true;
}
```
到这里消息才被添加进消息队列，然后就交由Looper.loop函数驱动队列消息的处理，这又回到开始的dispatchMessage函数。

# 总结
- 通过Looper的prepare方法创建MessageQueue
- 通过loop方法找到和当前线程匹配的Looper对象me
- 从me中取出消息队列对象mQueue
- 在一个死循环中，从mQueue中取出Message对象
- 调用每个Message对象的msg.target.dispatchMesssge方法
- 也就是Handler的dispatchMessage 方法
- 在dispatchMessage 根据Message对象的特点执行特定的方法。
