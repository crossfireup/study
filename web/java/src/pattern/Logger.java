public class Logger {
    private static Logger instance = NULL;

    private Logger()
    {
    }

    public synchronized static Logger getInstance(){

        if (instance == NULL){
            instance = new Logger();
        }

        return instance;
    }

    private class LoggerHolder {
        public static final Logger instance = new Logger();
    }

    public static Logger getInstanceEff(){
        return LoggerHolder.instance;
    }

    public void log (String message)
    {
        System.out.println(System.currentTimeMillis + ": " + message);
    }

}
