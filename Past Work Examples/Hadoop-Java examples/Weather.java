import java.io.IOException;
import java.lang.String;
import java.lang.Math;

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

public class Weather 
{

  public static double Rlat;
  public static double Rlong;


  public static class TokenizerMapper 
       extends Mapper<Object, Text, Text, DoubleWritable>
  {

    public double distance(double lat1, double long1)
    {
      double O1, O2, L1, L2, ER;

      O1 = Rlat * Math.PI / 180.0;
      O2 = lat1 * Math.PI / 180.0;
      L1 = Rlong * Math.PI / 180.0;
      L2 = long1 * Math.PI / 180.0;
      ER = 3963.19;

      double dLat = O2 - O1;
      double dLong = L2 - L1;

      return(2 * ER * Math.asin(Math.sqrt(haversine(dLat) + Math.cos(O1) * Math.cos(O2) * haversine(dLong))));
    }

    public double haversine(double angle)
    {
      return((1 - Math.cos(angle)) / 2.0);
    }


    public void map(Object key, Text value, Context context
                    ) throws IOException, InterruptedException 
    {
      String line = new String(value.toString());
      double lat1 = Double.parseDouble(line.substring(28, 33));
      double long1 = Double.parseDouble(line.substring(34, 40));
      double tmp = Double.parseDouble(line.substring(87, 91));
      String yr = new String(line.substring(15,18));

      if(!line.substring(87,90).equals("+9999"))
      {
        lat1 = lat1 / 1000;
        long1 = long1 / 1000;
        tmp = tmp / 10;

        DoubleWritable temp = new DoubleWritable(tmp);
        Text year = new Text(yr);

        if(distance(lat1, long1) <= 50.0)
        {
	  context.write(year, temp);
        }
      }
    }
  }
  
  public static class IntSumReducer 
       extends Reducer<Text,DoubleWritable,Text,DoubleWritable> 
  {
    private DoubleWritable result = new DoubleWritable();

    public void reduce(Text key, Iterable<DoubleWritable> values, 
                       Context context
                       ) throws IOException, InterruptedException 
    {
      double sum = 0;
      double count = 0;
      
      for (DoubleWritable val : values)
      {
        sum += val.get();
	count += 1;
      }

      result.set(32 + (sum / count) * (9.0 / 5.0));
      context.write(key, result);
      
    }
  }

  public static class Comb
       extends Reducer<Text,DoubleWritable,Text,DoubleWritable>
  {
    public void reduce(Text key, Iterable<DoubleWritable> values,
                       Context context
                       ) throws IOException, InterruptedException
    {
      for(DoubleWritable val : values)
      {
	context.write(key, val);
      }
    }
  }


  public static void main(String[] args) throws Exception 
  {
    Configuration conf = new Configuration();
    String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
    if (otherArgs.length != 4) 
    {
      System.err.println("Usage: weather <in> <out> <refernce latitude> <reference longitude>");
      System.exit(2);
    }

    Rlat = Double.parseDouble(otherArgs[2]);
    Rlong = Double.parseDouble(otherArgs[3]);

    Job job = Job.getInstance(conf, "weather");
    job.setJarByClass(Weather.class);
    job.setMapperClass(TokenizerMapper.class);
    job.setCombinerClass(Comb.class);
    job.setReducerClass(IntSumReducer.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(DoubleWritable.class);
    FileInputFormat.addInputPath(job, new Path(otherArgs[0]));
    FileOutputFormat.setOutputPath(job, new Path(otherArgs[1]));
    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}
