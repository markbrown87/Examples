/* Created by Mark Brown
 * Date: 23/4/2018
 * Description: This file contains the calls to a database for regarding a
 *	nature reserve. Departments, Employees, and Animals are all recorded on this
 *	database which can be queried as well as return useful results.
 *
 */

import java.io.*; 
import java.sql.*;

class nature {
	public static void main(String args []) throws SQLException, IOException{

		Useful_Calls UC = new Useful_Calls();
		boolean done;
		char ch,ch1;
		byte num = 0;

		try {
			Class.forName ("oracle.jdbc.driver.OracleDriver");
		} catch (ClassNotFoundException e) {
			System.out.println ("Could not load the driver");
			return;
		}
		String user, pass;
		user = "mbrown";
		pass = "mb577273";
		/*
		user = readEntry("userid  : ");
		pass = readEntry("password: ");
		*/

		//  The following line was modified by Prof. Marling to work on prime

		Connection conn = DriverManager.getConnection
				("jdbc:oracle:thin:@deuce.cs.ohiou.edu:1521:class", user, pass);

		done = false;
		do {
			UC.print_menu();
			System.out.print("Type in your option:");
			System.out.flush();
			ch = (char) System.in.read();
			ch1 = (char) System.in.read();
			switch (ch) {
				case '1' : UC.display_table(conn);
					break;
				case '2' : UC.add_employee(conn);
					break;
				case '3' : UC.delete_employee(conn);
					break;
				case '4' : UC.modify_employee(conn);
					break;
				case '5' : UC.trapper_report(conn);
					break;
				case '6': UC.pamphlet(conn);
					break;
				case 'q' : done = true;
					break;
				default  : System.out.println("Type in option again");
			}
			System.out.println("\n");
		} while (!done);

		conn.close();
	}

    //readEntry function -- to read input string
    static String readEntry(String prompt) {
        try {
            StringBuffer buffer = new StringBuffer();
            System.out.print(prompt);
            System.out.flush();
            int c = System.in.read();
            while(c != '\n' && c != -1) {
                buffer.append((char)c);
                c = System.in.read();
            }
            return buffer.toString().trim();
        } catch (IOException e) {
            return "";
        }
    }
}