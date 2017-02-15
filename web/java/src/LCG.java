public class LCG 
{
    public static int rand_state;

    public void my_srand(int init){
        rand_state = init;
    }

    private static int RAN_a = 1664525;
    private static int RAN_c = 1013904223;

    public int my_rand()
    {
        rand_state = rand_state * RAN_a;
        rand_state = rand_state + RAN_c;
        return rand_state & 0x7fff;
    }
}
