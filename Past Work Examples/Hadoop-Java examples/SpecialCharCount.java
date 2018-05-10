import java.io.IOException;
import java.util.StringTokenizer;
import java.lang.Object;
import java.lang.Integer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

// Count the number of special characters in a the input
public class SpecialCharCount {

  public static class CharCountMapper 
       extends Mapper<Object, Text, Text, IntWritable>{
    
    private final static IntWritable one = new IntWritable(1);
      
    public void map(Object key, Text value, Context context
                    ) throws IOException, InterruptedException {
	int i=0;
	while (i<value.getLength()) {
		//byte myTest = value.charAt(i);
		//System.out.println(value.charAt(i));
		byte signed = (byte)value.charAt(i);
		int myLong = signed & (0xff);
		//System.out.println("myInt: " + myInt);
	    if (myLong > 128) {
		System.out.println("myInt: " + myLong);
		Integer r = new Integer(value.charAt(i));
		StringBuffer t = new StringBuffer();
		
		t.append(r.toString());
		Text t1 = new Text(t.toString());
		context.write(t1, one);
		//i++;
	    } 
		i++;
	}
      }
    
  }
  
  public static class MyReducer 
       extends Reducer<Text,IntWritable,Text,IntWritable> {
    private IntWritable result = new IntWritable();

    public void reduce(Text key, Iterable<IntWritable> values, 
                       Context context
                       ) throws IOException, InterruptedException {
      int sum = 0;
      for (IntWritable val : values) {
        sum += val.get();
      }
      result.set(sum);
      context.write(key, result);
    }
  }

  public static void main(String[] args) throws Exception {
    Configuration conf = new Configuration();
    String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
    if (otherArgs.length != 2) {
      System.err.println("Usage: linelengthcount <in> <out>");
      System.exit(2);
    }
    Job job = Job.getInstance(conf, "SpecialCharCount");
    job.setJarByClass(SpecialCharCount.class);
    job.setMapperClass(CharCountMapper.class);
    job.setCombinerClass(MyReducer.class);
    job.setReducerClass(MyReducer.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);
    FileInputFormat.addInputPath(job, new Path(otherArgs[0]));
    FileOutputFormat.setOutputPath(job, new Path(otherArgs[1]));
    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}
