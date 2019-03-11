#Android 学习笔记

##TextView
- android:text 文本内容
- android:gravity 对齐方向
- android:textStyle 字体类型（粗体，斜体等）
- android:textSize 字体大小
- android:textColor 字体颜色
- android:background 背景颜色，也可以设置drawable资源（边框背景）

- android:shadowColor 阴影颜色
- android:shadowRadius 阴影模糊程度（这个属性不是很理解）
- android:shadowDx 阴影的水平偏移
- android:shadowDy 阴影的垂直偏移

- android:drawableTop 上方图片，设置图片大小需要调用getCompoundDrawables()，setBound，setCompoundDrawables
- android:drawableLeft
- android:drawableRight
- android:drawableBottom
- android:drawablePadding 图片与文字的间距

- android:autoLink 自动识别文本中的链接类型，点击可以跳转到对应的Activity，需要调用setMovementMethod(LinkMovementMethod.getInstance()) 

- android:ellipsize="marquee"
- android:singleLine="true"
- android:marqueeRepeatLimit="marquee_forever" 设置跑马灯效果，还需要调用TextView.setSelected(true)

##TextEdit
- android:selectAllOnFocus 获取焦点时全选文本
- android:inputType 设置可接受的输入类型（电话，邮件，数组，字母等）
- android:minLines
- android:maxLines 设置显示行数
- android:singleLine="true" 设置单行显示