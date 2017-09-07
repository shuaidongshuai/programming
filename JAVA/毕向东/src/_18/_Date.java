package _18;

import java.text.SimpleDateFormat;
import java.time.Year;
import java.util.Calendar;
import java.util.Date;

public class _Date {
	public static void main1(String[] args) {
		Date d = new Date();
		System.out.println(d);
		
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyÄêMMÔÂddÈÕ     E  HH:mm:ss");
		String s = sdf.format(d);
		System.out.println(s);
	}
	public static void main(String[] args) {
		Calendar c = Calendar.getInstance(); 
		System.out.println(c);
		System.out.println(c.get(Calendar.YEAR));
	}
}
