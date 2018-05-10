// Reads Twitter Data using JSON object parser.
import org.json.*;
import java.math.*;
import java.awt.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

class ReadTwitter {
public static void main(String argv[]) {

    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    
    String input;
    try {
	while((input=br.readLine())!=null){
	    JSONObject jsn = new JSONObject(input);
	    JSONObject actor_object;
	    String text;
	    String name;
	    try {
		text = (String) jsn.get("text");
	    } catch (JSONException je) {
		text = (String) "missing tweet";
	    }
	    try {
		actor_object =  jsn.getJSONObject("user");
		try {
		    name = (String) actor_object.get("screen_name");
		} catch (JSONException je2) {
		    name = (String) "Missing user???";
		}
	    } catch (JSONException je1) {
		name = (String) "missing user object";
	    }
	    System.out.println("Name = "+name+" Tweet text:"+text);
	}
    } catch(IOException io){
	System.out.println("IO Error --- ");
	io.printStackTrace();
    }	
}
}
    
