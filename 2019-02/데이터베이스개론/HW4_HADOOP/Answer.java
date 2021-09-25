/*
   Copyright 2019 The Apache Software Foundation

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
import java.io.IOException;
import java.util.ArrayList;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.ArrayWritable;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.MultipleInputs;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class Answer {

	public static class StuMapper extends Mapper <Object, Text, Text, Text> {
		public void map(Object key, Text value, Context context)
				throws IOException, InterruptedException {
			// =============== WRITE YOUR CODE =====================
			String record = value.toString();
			String[] parts = record.split(",");
			context.write(new Text(parts[4]), new Text("student," + parts[5]));
			
			// =====================================================
		}
 	}
 
	public static class DeptMapper extends Mapper <Object, Text, Text, Text> {
		public void map(Object key, Text value, Context context) 
				throws IOException, InterruptedException {
			// =============== WRITE YOUR CODE =====================
			String record = value.toString();
			String[] parts = record.split(",");
			context.write(new Text(parts[0]), new Text("dept," + parts[1] + "," + parts[2]));
	
			// =====================================================
		}
	}
 
 	public static class AnswerReducer extends Reducer <Text, Text, Text, Text> {
		public void reduce(Text key, Iterable<Text> values, Context context)
				throws IOException, InterruptedException {
			
			// =============== WRITE YOUR CODE =====================
			String dname = "";
			String dcampus = "";
			int gpa_cnt = 0;
			float max_gpa = -1;
			float avg_gpa = 0;
			float gpa_flo = -1;
			for (Text t: values) {
				String parts[]  = t.toString().split(",");
				if (parts[0].equals("student")){
					gpa_flo = Float.parseFloat(parts[1]);
					if(max_gpa < gpa_flo) max_gpa = gpa_flo;
					avg_gpa += gpa_flo;
					gpa_cnt++;
				}
				else if (parts[0].equals("dept")) {
					dname = parts[1];
					dcampus = parts[2];
				}
			}
			avg_gpa /= gpa_cnt;
			if(avg_gpa > 3.5 && !dname.equals("")) context.write(new Text(dname), new Text(Float.toString(max_gpa)+" "+dcampus));
			// =====================================================
 		}
 	}
 
	public static void main(String[] args) throws Exception {
		Configuration conf = new Configuration();
		Job job = new Job(conf, "Reduce-side join");
		job.setJarByClass(Answer.class);
		job.setReducerClass(AnswerReducer.class);
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);
  
		MultipleInputs.addInputPath(job, new Path(args[0]),TextInputFormat.class, StuMapper.class);
		MultipleInputs.addInputPath(job, new Path(args[1]),TextInputFormat.class, DeptMapper.class);
		Path outputPath = new Path(args[2]);
  
		FileOutputFormat.setOutputPath(job, outputPath);
		outputPath.getFileSystem(conf).delete(outputPath);
		System.exit(job.waitForCompletion(true) ? 0 : 1);
	}
}
