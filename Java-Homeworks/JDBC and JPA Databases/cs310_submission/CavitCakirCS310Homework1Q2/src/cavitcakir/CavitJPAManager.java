package cavitcakir;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

import cavitcakir.Country;

public class CavitJPAManager {
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
			System.out.println("file done");
		
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
	

	public static void writeIntoTable( ArrayList<Country> countries ) {
		
		EntityManagerFactory emf = Persistence.createEntityManagerFactory("cs310");
		EntityManager entityManager =emf.createEntityManager();
		
		entityManager.getTransaction().begin();
		for (Country s : countries)
		{
			entityManager.persist(s);
		}
		System.out.println("database filled");
		
		entityManager.getTransaction().commit();
	}

	public static Country getCountryByID(int countryID) {
		Country s;
		EntityManagerFactory emf = Persistence.createEntityManagerFactory("cs310");
		EntityManager entityManager =emf.createEntityManager();
		entityManager.getTransaction().begin();
		s = entityManager.find(Country.class, countryID);
		entityManager.getTransaction().commit();
		if(s == null) {
			System.out.println("cannot find that country");
			s = new Country("-1","-1","-1",-1);
		}
		else {
			System.out.println("found.");
		}
		return s;
	}
	
	public static void deleteCountryByID (int countryID) {
		EntityManagerFactory emf = Persistence.createEntityManagerFactory("cs310");
		EntityManager entityManager =emf.createEntityManager();
		
		entityManager.getTransaction().begin();
		Country s = entityManager.find(Country.class, countryID);
		if(s != null) {
			entityManager.remove(s);
			System.out.println("deleted");
		}else {
			System.out.println("cannot find that country");
		}
		entityManager.getTransaction().commit();
	}
	
	public static void updateCountryPopulationByID (int countryID, int population) {
		EntityManagerFactory emf = Persistence.createEntityManagerFactory("cs310");
		EntityManager entityManager =emf.createEntityManager();
		
		entityManager.getTransaction().begin();
		Country s = entityManager.find(Country.class, countryID);
		if(s != null) {
			s.setPopulation(population);
			System.out.println("updated");
		}else {
			System.out.println("cannot find that country");
		}
		entityManager.getTransaction().commit();	
	}
}