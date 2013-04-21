/*
 * EdgeD.jar предназначен для открытия интернет сессии
 * EdgeD.elf перехватывает ид сессии и использует для эльфов
 */
 
package edged;

import java.io.*;
import javax.microedition.io.*;
import javax.microedition.lcdui.*;
import javax.microedition.midlet.*;

/**
 * @author vova7890
 */
public class Midlet extends MIDlet implements CommandListener {

    boolean applicationStarted = false;
    Form form;
    Display display;
    Command connectCmd, exitCmd;
    
    public void startApp() {
        
        if(applicationStarted)
            return;
        applicationStarted = true;
        
        form = new Form("Disconnected");
        form.setCommandListener(this);
        
        display = Display.getDisplay(this);
        display.setCurrent(form);
        
        connectCmd = new Command("Connect", Command.OK, 1);
        exitCmd = new Command("Exit", Command.EXIT, 2);

        form.addCommand(connectCmd);
        form.addCommand(exitCmd);
    }
    
    
    void startSession() {
        
        form.setTitle("Connecting...");
        
        try {
            HttpConnection connection = (HttpConnection) Connector.open("http://google.com");
            connection.setRequestMethod(HttpConnection.GET);
            
            OutputStream os = connection.openOutputStream();
            InputStream is = connection.openInputStream();
            
            os.close();
            is.close();
            connection.close();
            
            form.setTitle("Connected");
            
        } catch (IOException ex) {
            form.setTitle("Exception handled");
        }
    }
    
    public void pauseApp() {
    }
    
    public void destroyApp(boolean unconditional) {
    }
    
    public void commandAction(Command c, Displayable d) {
        
        if(c == connectCmd) {
            
            new Thread( new Runnable() {
                
                public void run() {
                    startSession();
                }
            }).start();
        } 
        
        else if(c == exitCmd) {
            notifyDestroyed();
        }
    }
}
