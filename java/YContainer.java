import java.lang.Math;
import java.util.ArrayList;
import java.util.Arrays;
import java.lang.String;

public class YContainer {
    public static class TestObj {
        int i;

        public TestObj() {
            i = (int) (Math.random() * 100);
        }

        public int value() {
            return i;
        }

        @Override
        public String toString() {
            return String.valueOf(i);
        }
    }

    public static void main(String args[]) {
        int cnt = 10;
        ArrayList<TestObj> data = new ArrayList<>();
        for (int i = 0; i < cnt; ++i)
            data.add(new TestObj());

        TestObj dest = data.get((int) (Math.random() * 10));
        int ret = -1;
        for (TestObj obj : data) {
            if (obj.value() == dest.value()) {
                ret = data.indexOf(obj);
                break;
            }
        }
        System.out.println(String.format("find value:%d in pos:%d", dest.value(), ret));
        System.out.println("data:" + Arrays.toString(data.toArray()));
        System.out.println("============testStringCmp============");
        testStringCmp();
    }

    public static void testStringCmp() {
        String str1 = "the light";

        String str2 = new String(str1);

        String str3 = str1.toUpperCase();

        // ==用于判断是否是同一个字符串对象
        System.out.println(str1 == str2);

        System.out.println(str1.equals(str2));// 完全一样返回true

        System.out.println(str1.equals(str3));// 大小写不一样，返回false
        System.out.println(str1.equalsIgnoreCase(str3));// 忽略大小写的比较，返回true
    }
}