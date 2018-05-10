import org.json.*;
import java.math.*;
import java.awt.*;
import java.io.*;
import java.util.*;
import java.util.HashMap;
import java.lang.*;


class MeanTweet{

    private static Scanner file;
    private static String word;
    private static double number;
    public static HashMap<String, Double> mean_map;
    public static HashMap<String, Double> tweet_map;
    public static HashMap<String, Double> tweeter_count;

    public static void open_sampleTxt(){
            try{
                file = new Scanner(new File("sample.txt"));
            }
            catch(Exception e){
                System.out.println("Error finding file");
            }
    }

    public static void read_sampleTxt(){
        String tmp;
        int value;
        mean_map = new HashMap<String, Double>();

        while(file.hasNext()){
            word = file.next();
            tmp = file.next();
            number = Integer.parseInt(tmp);

            mean_map.put(word, number);
        }
    }

    public static void read_meanTweets(String[] argv){

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        tweet_map = new HashMap<String,Double>();
        tweeter_count = new HashMap<String, Double>();
        double tweet_value = 0;
        double tweet_amount = 1;

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
                        name = (String) "missing user object";
                    }
                } catch (JSONException je1) {
                    name = (String) "missing user object";
                }

                if(!name.equals("missing user object"))
                    if(!text.equals("missing tweet")){
                        tweet_value = parse_tweet(text);
                        if(tweet_map.containsKey(name)){
                            double tmp = tweet_map.get(name);
                            double count = tweeter_count.get(name);
                            tmp += tweet_value;
                            count++;
                            tweet_map.put(name, tmp);
                            tweeter_count.put(name, count);
                        }
                        else{
                            tweet_map.put(name, tweet_value);
                            tweeter_count.put(name, tweet_amount);
                        }
                    }
            }
        } catch(IOException io) {
            System.out.println("IO Error --- ");
            io.printStackTrace();
        }
    }

    public static double parse_tweet(String tweet){
        String[] words = tweet.replaceAll("\\p{P}", "").toLowerCase().split("\\s+");
        double tmp = 5;

        for(int i = 0; i < words.length; ++i){
            if(mean_map.containsKey(words[i])){
                if(tmp > mean_map.get(words[i]))
                    tmp = mean_map.get(words[i]);
            }
        }
        return tmp;
    }

//    public static void main(String[] argv){
//        open_sampleTxt();
//        read_sampleTxt();
//        read_meanTweets(argv);
//
//        double sum = 0;
//
//        for (String name: tweet_map.keySet()){
//
//            String key = name.toString();
//            double value = tweet_map.get(name);
//            double count = tweeter_count.get(name);
//            sum += count;
//            double si = value / count;
//
//            System.out.println(key + " Value: " + value + " Count: " + count + " S(I): " + si);
//
//
//        }
//        System.out.println("Total amount of Tweets: " + sum);
//    }

}