package cavitcakir.jdbc;
import cavitcakir.jdbc.Country;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;



public class CavitJDBCManager {
	public static ArrayList<Country> readFromFile(String filename)
	{
		ArrayList<Country> countries = new ArrayList<Country>();
		try 
		{
			FileReader reader = new FileReader(filename);
			BufferedReader bfr = new BufferedReader(reader);
			while(true)
			{
				String line = bfr.readLine();
				if (line == null)
				{
					break;
				}
				//System.out.println(line);
				String[] arr = line.split(",");
				String name = arr[0];
				String region = arr[1];
				String city = arr[2];
				int population = Integer.parseInt(arr[3]);
				Country s = new Country(name, region, city, population);
				
				countries.add(s);
			}
			reader.close();
			System.out.println("file done.");
		
		}
		catch (FileNotFoundException e) {
			System.out.println("no file");
			e.printStackTrace();
		}
		catch (IOException e) {
			System.out.println("no have rights to read that file");
			e.printStackTrace();
		}
		return countries;
	}
	
	public static void createDB() {
		String sql = "CREATE TABLE Countries (" +
				"countryID int NOT NULL AUTO_INCREMENT, " +
                " name VARCHAR(255), " + 
                " region VARCHAR(255), " +
                " city VARCHAR(255), " +
                " population INT, "+
                " PRIMARY KEY (countryID))";
		
		try {
			Connection connection = DriverManager.getConnection("jdbc:mysql://127.0.0.1/cs310", "root", "123123123");
			Statement stmt = connection.createStatement();
			stmt.executeUpdate(sql);
			System.out.println("Table created!!!");
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static void writeIntoTable( ArrayList<Country> countries ) {
		try
		{
			Connection connection = DriverManager.getConnection("jdbc:mysql://127.0.0.1/cs310", "root", "123123123");
			for (Country s : countries)
			{
				PreparedStatement ps =  connection.prepareStatement("insert into Countries (population,name,region,city) values (?,?,?,?) ");
				ps.setInt(1, s.getPopulation());
				ps.setString(2, s.getName());
				ps.setString(3, s.getRegion());
				ps.setString(4, s.getCity());
				ps.execute();
			}
			
			System.out.println("Data inserted!!!");
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		
	}
	
	public static Country getCountryByID(int countryID) {
		Country s;
		try
		{
			Connection connection = DriverManager.getConnection("jdbc:mysql://127.0.0.1/cs310", "root", "123123123");	
			PreparedStatement ps =  connection.prepareStatement("select name,region,city,population from Countries where countryID=?");
			ps.setInt(1, countryID);
			
			ResultSet rs =	ps.executeQuery();
			if(rs.next())
			{
				String name = rs.getString("name");
				String region = rs.getString("region");
				String city = rs.getString("city");
				int population = rs.getInt("population");
				s = new Country(name, region, city, population);
				System.out.println("found.");
			}
			else {
				System.out.println("cannot find that country");
				s = new Country("-1", "-1", "-1", -1);	
			}
		}
		catch (Exception e) {
			System.out.println("cannot find that country");
			s = new Country("-1", "-1", "-1", -1);
			e.printStackTrace();
		}
		return s;
	}
	
	public static void deleteCountryByID (int countryID) {
		try
		{
			Connection connection = DriverManager.getConnection("jdbc:mysql://127.0.0.1/cs310", "root", "123123123");	
			PreparedStatement ps =  connection.prepareStatement("DELETE FROM Countries WHERE countryID=?");
			ps.setInt(1, countryID);
			int rs = ps.executeUpdate();
			if(rs!=0) {
				System.out.println("deleted");
			}
			else {
				System.out.println("cannot find");
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void updateCountryPopulationByID (int countryID, int population) {
		try
		{
			Connection connection = DriverManager.getConnection("jdbc:mysql://127.0.0.1/cs310", "root", "123123123");	
			PreparedStatement ps =  connection.prepareStatement("update Countries set population=? where countryID=? ");
			ps.setInt(1, population);
			ps.setInt(2, countryID);
			int rs = ps.executeUpdate();
			if(rs!=0) {
				System.out.println("updated");
			}
			else {
				System.out.println("cannot find");
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
}
