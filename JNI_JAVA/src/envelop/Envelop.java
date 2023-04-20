package src.envelop;
/*javac .\src\envelop\Envelop.java -h */

public class Envelop {
    public native long  GetEnvelopPoint();
    public native String GetPublicString(long envelop_point);
    public native String Encode(long  envelop_point,String pubstr,String message);
    public native String Decode(long envelop_point,String message);
    public native void FreeEnvelopPoint(long envelop_point);
}
