package cavitcakir;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;

@Entity
public class Country {
	
	@Id @GeneratedValue
	private int countryID;
	
	private String name;
	private String region;
	private String city;
	private int population;
	
	
	public Country() {
		super();
	}
	public Country(String name, String region, String city, int population) {
		super();
		this.name = name;
		this.region = region;
		this.city = city;
		this.population = population;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getRegion() {
		return region;
	}
	public void setRegion(String region) {
		this.region = region;
	}
	public String getCity() {
		return city;
	}
	public void setCity(String city) {
		this.city = city;
	}
	public int getPopulation() {
		return population;
	}
	public void setPopulation(int population) {
		this.population = population;
	}

}
