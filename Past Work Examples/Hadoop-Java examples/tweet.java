import org.json.*;
import java.math.*;
import java.awt.*;
import java.io.*;
import java.util.*;
import java.util.HashMap;
import java.lang.*;
import java.net.*;


import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;


public class tweet {

    public static class TokenizerMapper
            extends Mapper<Object, Text, Text, DoubleWritable>{

        private final static DoubleWritable one = new DoubleWritable(0);
        private Text word = new Text();
        private static Scanner file;
        private static String line;
        private static double number;
        public static HashMap<String, Double> my_map;
        public static HashMap<String, Double> my_map2;
//public static HashMap<String, Double> my_map3;

        public void setup(Context context) throws IOException, InterruptedException {
            String tmp;
            double value;
            try{
                file = new Scanner(new File(context.getCacheFiles().toString() ));
            }
            catch(Exception e) {
                System.out.println("Error finding file");
            }


            my_map = new HashMap<String, Double>();

            while(file.hasNext()) {
                line = file.next();
                tmp = file.next();
                number = Double.parseDouble(tmp);

                my_map.put(line, number);
            }
            //Read tweets


        }

        public static double getScore(String text){
            String [] words = text.replaceAll("\\p{P}", "").toLowerCase().split("\\s+");
            double tmp = 5;
            for (String word : words) {
                if(my_map.containsKey(word)) {
                    if(tmp > my_map.get(word)) {
                        tmp = my_map.get(word);
                    }
                }
            }
            return tmp;

        }

        public void readJSON(String line){
            my_map2 = new HashMap<String, Double>();
        /*Path pt=new Path("hdfs:/input/toptwitter.json");//Location of file in HDFS
        FileSystem fs = FileSystem.get(new Configuration());
        BufferedReader br=new BufferedReader(new InputStreamReader(fs.open(pt)));
        */
            BufferedReader br = new BufferedReader(new StringReader(line));
            double tweets = 1.0;
            double score = 0.0;
            String input;
            try {
                while((input = br.readLine())!=null) {
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
                    if (!name.equals("missing user object")) {
                        if(!text.equals("missing tweet")) {
                            score = getScore(text);
                            my_map2.put(name, score);
                        }

                    }
                    //System.out.println("Name = "+name+" Tweet text:"+text);
                }

            } catch(IOException io) {
                System.out.println("IO Error --- ");
                io.printStackTrace();
            }
        }

        public void map(Object key, Text value, Context context
        ) throws IOException, InterruptedException {
            my_map2.clear();
            String line = value.toString();
            readJSON(line);
            for (Map.Entry<String, Double> entry : my_map2.entrySet()){
                String user = entry.getKey();
                word.set(user);
                double rating = entry.getValue();
                one.set(rating);
                context.write(word, one);
            }

        }
    }

    public static class TweetReducer
            extends Reducer<Text,DoubleWritable,Text,DoubleWritable> {
        private DoubleWritable result = new DoubleWritable();

        public void reduce(Text key, Iterable<DoubleWritable> values,
                           Context context
        ) throws IOException, InterruptedException {
            int sum = 0;
            for (DoubleWritable val : values) {
                sum += val.get();
            }
            result.set(sum);
            context.write(key, result);
        }
    }


    public static void main(String[] args) throws Exception {
        Configuration conf = new Configuration();
        String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
        if (otherArgs.length != 3) {
            System.err.println("Usage: tweets <in> <out>");
            System.exit(2);
        }
        //hdfs
        //use jobcache
        Job job = Job.getInstance(conf, "MeanTweeters");
        job.setJarByClass(tweet.class);
        job.setMapperClass(TokenizerMapper.class);
        job.setCombinerClass(TweetReducer.class);
        job.setReducerClass(TweetReducer.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(DoubleWritable.class);
        job.addCacheFile(new Path(otherArgs[0]).toUri());
        FileInputFormat.addInputPath(job, new Path(otherArgs[1]));
        FileOutputFormat.setOutputPath(job, new Path(otherArgs[2]));
        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }

//
//    public static HashMap<String, Double> mean_map;
//    private static Scanner file;
//    private static String word;
//    private static double number;
////    public static HashMap<String, Double> tweet_map;
////    public static HashMap<String, Double> tweeter_count;
//
//    public static class CharCountMapper
//            extends Mapper<Object, Text, Text, DoubleWritable>{
//        private static DoubleWritable tweet_value = new DoubleWritable();
//        //private HashMap<String, Double> mean_map;
//        //private Scanner file;
//       // private final static DoubleWritable one = new DoubleWritable(1);
//
//        public void setup(Context context) throws IOException, InterruptedException {
//            Configuration conf = context.getConfiguration();
//            try{
//                URI[] uris = context.getCacheFiles();
//                for (URI uri : uris) {
//                    if (uri.toString().endsWith("sample.txt")) {
//                        file = new Scanner(new File(uri));
//                    }
//                }
//                //URI[] uri = context.getCacheFiles();
//                file = new Scanner(new File(context.getCacheFiles().toString()));
//            }
//            catch(Exception e){
//                System.out.println("Error finding file");
//            }
//
//            String tmp;
//            //int value;
//            mean_map = new HashMap<String, Double>();
//
//            while(file.hasNext()){
//                word = file.next();
//                tmp = file.next();
//                number = Integer.parseInt(tmp);
//
//                mean_map.put(word, number);
//            }
//        }
//
//        public void map(Object key, Text value, Context context
//        ) throws IOException, InterruptedException {
//
//            double tweet_amount = 1;
//
//            try {
//                    JSONObject jsn = new JSONObject(value);
//                    JSONObject actor_object;
//                    String text;
//                    String name;
//                    try {
//                        text = (String) jsn.get("text");
//                    } catch (JSONException je) {
//                        text = (String) "missing tweet";
//                    }
//                    try {
//                        actor_object =  jsn.getJSONObject("user");
//                        try {
//                            name = (String) actor_object.get("screen_name");
//                        } catch (JSONException je2) {
//                            name = (String) "missing user object";
//                        }
//                    } catch (JSONException je1) {
//                        name = (String) "missing user object";
//                    }
//
//                    if(!name.equals("missing user object"))
//                        if(!text.equals("missing tweet")){
//                            tweet_value = parse_tweet(text);
//                            Text tmp = new Text(name);
//                            context.write(tmp, tweet_value);
//                        }
//
//            } catch(IOException io) {
//                System.out.println("IO Error --- ");
//                io.printStackTrace();
//            }
//        }
//
//        public DoubleWritable parse_tweet(String tweet){
//            String[] words = tweet.replaceAll("\\p{P}", "").toLowerCase().split("\\s+");
//            double tmp = 5;
//
//            for(int i = 0; i < words.length; ++i){
//                if(mean_map.containsKey(words[i])){
//                    if(tmp > mean_map.get(words[i]))
//                        tmp = mean_map.get(words[i]);
//                }
//            }
//
//            DoubleWritable result = new DoubleWritable(tmp);
//            return result;
//        }
//
//    }
//
//    public static class MyReducer
//            extends Reducer<Text,DoubleWritable,Text,DoubleWritable> {
//        private final static DoubleWritable result = new DoubleWritable();
//
//        public void reduce(Text key, Iterable<DoubleWritable> values,
//                           Context context
//        ) throws IOException, InterruptedException {
//            int sum = 0;
//            for (DoubleWritable val : values) {
//                sum += val.get();
//            }
//            result.set(sum);
//            context.write(key, result);
//        }
//    }
//
//    public static void main(String[] args) throws Exception {
//        System.setProperty("file.encoding", "ISO-8859-5");
//
//        Configuration conf = new Configuration();
//        String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
//        if (otherArgs.length != 3) {
//            System.err.println("Usage: linelengthcount <in> <out>");
//            System.exit(2);
//        }
//
//        Job job = Job.getInstance(conf, "MeanTweets");
//        job.addCacheFile(new Path(otherArgs[0]).toUri());
//        job.setJarByClass(tweet.class);
//        job.setMapperClass(CharCountMapper.class);
//        job.setCombinerClass(MyReducer.class);
//        job.setReducerClass(MyReducer.class);
//        job.setOutputKeyClass(Text.class);
//        job.setOutputValueClass(DoubleWritable.class);
//        FileInputFormat.addInputPath(job, new Path(otherArgs[1]));
//        FileOutputFormat.setOutputPath(job, new Path(otherArgs[2]));
//        System.exit(job.waitForCompletion(true) ? 0 : 1);
//    }
}