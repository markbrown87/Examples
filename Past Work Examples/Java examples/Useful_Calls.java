/* Created by Mark Brown
 * Date: 23/4/2018
 * Description: This file contains the calls to a database for regarding a
 *	nature reserve. Departments, Employees, and Animals are all recorded on this
 *	database which can be queried as well as return useful results.
 *
 */

import java.sql.*; 
import java.io.*; 

class Useful_Calls{

    void print_menu() {
        System.out.println(" Bruin's Bay National Park\n");
        System.out.println("(1) Display Employee Table");
        System.out.println("(2) Add New Employee");
        System.out.println("(3) Delete Employee");
        System.out.println("(4) Modify Employee");
        System.out.println("(5) Trapper Report");
        System.out.println("(6) Pamphlet");
        System.out.println("(q) Quit\n");
    }


    // Displays the information from Employees from the database
    void display_table(Connection conn)
            throws SQLException, IOException {

        Statement stmt = conn.createStatement();

        String query = "select * from employees";
        ResultSet rset = stmt.executeQuery(query);

        try {
            System.out.println("");
            System.out.println("EPID\tNAME\t\tSALARY\tADDRESS\t\t\tDEPT#");
            while (rset.next ()) {
                System.out.println(rset.getString(1) + "\t" +
                        rset.getString(2) + "\t" +
                        rset.getString(3) + "\t" +
                        rset.getString(4) + "\t\t" +
                        rset.getString(5));
            }
        } catch (SQLException e) {
            System.out.println("Error selecting employee information from table.");
            while (e != null) {
                System.out.println("Message     : " + e.getMessage());
                e = e.getNextException();
            }
            return;
        }
        stmt.close();
        System.out.println("Employee table information shown.\n");
    }

    // Inserts into the database a new employee
    void add_employee(Connection conn)
            throws SQLException, IOException {

        Statement stmt = conn.createStatement();

        System.out.println("Please add new Employee information below.");
        String emp_id       = readEntry("ID        : ");
        String emp_name     = readEntry("Name      : ");
        String emp_salary   = readEntry("Salary    : ");
        String emp_address  = readEntry("Address   : ");
        String emp_dept     = readEntry("Department: ");

        String query = "insert into employees values (" + emp_id + ",'" + emp_name + "'," + emp_salary + ",'" +
                emp_address + "', " + emp_dept + ")";
        try {
            int nrows = stmt.executeUpdate(query);
        } catch (SQLException e) {
            System.out.println("Error Adding New Employee");
            while (e != null) {
                System.out.println("Message     : " + e.getMessage());
                e = e.getNextException();
            }
            return;
        }
        stmt.close();
        System.out.println("Added New Employee\n");
    }

    // Deletes an employee from the table
    void delete_employee(Connection conn)
            throws SQLException, IOException {


        System.out.println("Removing Someone from Employees table.");

        String name = readEntry("Name : ");
        String query = "delete from employees where name = '" + name + "'";

        conn.setAutoCommit(false);
        Statement stmt = conn.createStatement ();
        int nrows;
        try {
            nrows = stmt.executeUpdate(query);
        } catch (SQLException e) {
            System.out.println("Could not delete employee: " + name +". They may not exist in database.");
            while (e != null) {
                System.out.println("Message     : " + e.getMessage());
                e = e.getNextException();
            }
            conn.rollback();
            return;
        }
        System.out.println("Deleted employee " + name + " from database.");
        conn.commit();
        conn.setAutoCommit(true);
        stmt.close();
    }

    // Modify a particular employee from database
    void modify_employee(Connection conn)
            throws SQLException, IOException {

        System.out.println("Please select who will have their salary modified.");
        String name   = readEntry("Name       : ");
        String salary = readEntry("New Salary : ");


        String query1 = "select salary from employees where name = '" + name + "'";
        String query2 = "update employees set salary = " + salary + " where name = '" + name + "'";

        Statement stmt = conn.createStatement ();
        try {
            ResultSet rset = stmt.executeQuery(query1);
            rset.next();
            System.out.println("Old salary : " + rset.getString(1));
            stmt.executeUpdate(query2);
        } catch (SQLException e) {
            System.out.println("Error updating or finding individual in Database");
            while (e != null) {
                System.out.println("Message     : " + e.getMessage());
                e = e.getNextException();
            }
            return;
        }
        System.out.println("Salary of " + name + " successfully updated to " + salary + ".");
        stmt.close();
    }

    // Prints out a tracker report
    void trapper_report(Connection conn)
            throws SQLException, IOException {

        String animal_count = "select count(*) from animal";
        String top_trapper = "select name , count(*) from animal join employees on eid=empid group by name";
        String bottom_trapper = "select name, count(*) from animal join employees on eid=empid group by name order by count(*) asc";

        Statement stmt = conn.createStatement ();
        try {
            ResultSet rset = stmt.executeQuery(animal_count);
            rset.next();
            System.out.println("Welcome to the Trapper Report.");
            System.out.println("Trappers this fiscal year have caught " + rset.getString(1) + " animals.");

            rset = stmt.executeQuery(top_trapper);
            rset.next();
            System.out.println("The top trapper is " + rset.getString(1) + " with a total of " + rset.getString(2) + " animals.");
            String top = rset.getString(1);

            rset = stmt.executeQuery(bottom_trapper);
            rset.next();
            System.out.println("The worst trapper is " + rset.getString(1) + " with a total of " + rset.getString(2) + " animals.");
            System.out.println("Suggestion: " + top + " should get a raise for being top tracker.");
            System.out.println("" + rset.getString(1) + " should be brought in for a more in depth performance review.");

            String answer = readEntry("Send email to " + rset.getString(1) + " about this issue? (y/n)");
            if(answer.equals("y")){
                System.out.println("" + rset.getString(1) +  " has been contacted regarding poor performance.");
            }
            else{
                System.out.println("" + rset.getString(1) + " was not contacted. You should reconsider.");
            }

            answer = readEntry("Give " + top + " a 10% raise for top performance? (y/n)");

            if(answer.equals("y")){
                String query1 = "select salary from employees where name = '" + top + "'";
                rset = stmt.executeQuery(query1);
                rset.next();
                System.out.println("Old salary : " + rset.getString(1));
                System.out.println("New salary : " + Double.parseDouble(rset.getString(1)) * 1.1);
                double tmp = Double.parseDouble(rset.getString(1)) * 1.1;
                String salary = Double.toString(tmp);
                String query2 = "update employees set salary = " + salary + " where name = '" + top + "'";
                stmt.executeUpdate(query2);

                System.out.println("" + top + " has been given a 10% and contacted about great performance this fiscal year.");
            }
            else{
                System.out.println("" + top + " was not given a raise... Government cut funding again? Imagine that.");
            }
        } catch (SQLException e) {
            System.out.println("Error printing out trapper report");
            while (e != null) {
                System.out.println("Message     : " + e.getMessage());
                e = e.getNextException();
            }
            return;
        }

        stmt.close();
    }

    // Prints out a tracker report
    void pamphlet(Connection conn)
            throws SQLException, IOException {

        String species = "select distinct species from animal";
        String seasonal_species = "select distinct species from animal where migration = 'Seasonal'";
        String small_pop = "select distinct species from animal where population = '<1000'";
        String vets = "select name from employees where dpid = '6'";
        String treated_animals = "select count(*) from animal";
        String contact = "select name from employees where dpid = '7'";

        String top_trapper = "select name , count(*) from animal join employees on eid=empid group by name";
        String bottom_trapper = "select name, count(*) from animal join employees on eid=empid group by name order by count(*) asc";

        Statement stmt = conn.createStatement ();
        System.out.println("                          Welcome to Bruins Bay National Park!");
        System.out.println("This wonderful park has many different species that you may encounter while on your travels.");
        try {
            ResultSet rset = stmt.executeQuery(species);
            rset.next();
            String tmp1 = rset.getString(1);
            rset.next();
            String tmp2 = rset.getString(1);
            rset.next();
            String tmp3 = rset.getString(1);
            System.out.println("     Species such as " + tmp1 + ", " + tmp2 + ", and " + tmp3 + " which are our most common.");

            rset = stmt.executeQuery(seasonal_species);
            rset.next();
            tmp1 = rset.getString(1);
            rset.next();
            tmp2 = rset.getString(1);
            rset.next();
            tmp3 = rset.getString(1);
            System.out.println("      Species such as " + tmp1 + ", " + tmp2 + ", and " + tmp3 + " are our seasonal visitors.");

            rset = stmt.executeQuery(small_pop);
            rset.next();
            tmp1 = rset.getString(1);
            rset.next();
            tmp2 = rset.getString(1);
            System.out.println("             We have small population animals such " + tmp1 + " or " + tmp2 + ".");
            System.out.println("");

            System.out.println("           This national park takes pride in looking after our furry friends.");

            rset = stmt.executeQuery(vets);
            rset.next();
            tmp1 = rset.getString(1);
            rset.next();
            tmp2 = rset.getString(1);
            System.out.println("          We have the best vets in the state like " + tmp1 + " and " + tmp2 + ".");
            System.out.println("");

            rset = stmt.executeQuery(treated_animals);
            rset.next();
            tmp1 = rset.getString(1);
            System.out.println("              Bruin's Bay National Park is here to look after our animals.");
            System.out.println("                      This year alone we have treated " + tmp1 + " animals");
            System.out.println("");

            System.out.println("      We hope that you enjoy your visit here. Please enjoy the wilderness and fresh air.");
            System.out.println("          If you are lucky you may see the golden bear that visits once a year.");
            System.out.println("Please make sure that you keep your cups safe if your name is Stanley. The Bruins love Stanley cups.");
            System.out.println("");

            rset = stmt.executeQuery(contact);
            rset.next();
            tmp1 = rset.getString(1);
            rset.next();
            tmp2 = rset.getString(1);
            System.out.println("     If you have any further questions please contact " + tmp1 + " or " + tmp2 + " for more help");
            System.out.println("                 Please keep the park clean and enjoy your stay here :)\n");

        } catch (SQLException e) {
            System.out.println("Error printing pamphlet");
            while (e != null) {
                System.out.println("Message     : " + e.getMessage());
                e = e.getNextException();
            }
            return;
        }

        stmt.close();
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
