import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

//class for student database
class Student
	{
		int roll_no;
		String dob;
		String address;
		String dept;
		String gender;

		// Contructor for saving details of a student
		Student(int t1,String t2,String t3,String t4,String t5)
		{
			roll_no=t1;
			dob=t2;
			address=t3;
			dept=t4;
			gender=t5;
		}
		void display()
		{
			System.out.println(roll_no+" "+dob+" "+address+" "+dept+" "+gender);
		}
	}


//main class begins
public class Linear_probing
{
	public static void main(String []args)
	{
		Random random = new Random();//creating a random object

		//values for univeral family of Hashing
		int a = random.nextInt(101-1) + 1;
		int b = random.nextInt(101-0) + 0;
		int key=0;

		//variables for statistics
		float comparisons=0, avg_compare,total=0;
		float load_factor;
		ArrayList<Student> studentList = new ArrayList<Student>();
		
		Student p = new Student(0,null,null,null,null);// p is variable for intializing array lists
		
		//reading input from file 
		try (BufferedReader br = new BufferedReader(new FileReader("hashing/inp_file2.txt")))
		{

			String sCurrentLine;
			
			while ((sCurrentLine = br.readLine()) != null) 
			{
				String[] elements = sCurrentLine.split(" ");
				int k = Integer.parseInt(elements[0]);
				Student s= new Student(k,elements[1],elements[2],elements[3],elements[4]);
				studentList.add(s);
				total++;
			}

		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		
		//defining main hash function
		List<ArrayList<Student>> main_hash = new ArrayList<ArrayList<Student>>(25);
		//Intializing main_hash function
		for(int i=0; i<25; i++)
		{
		main_hash.add(null);
		}
		
		for(int i=0; i<25; i++)
		{
			ArrayList<Student> inner_hash= new ArrayList<Student>();
			inner_hash.add(p);
			main_hash.set(i,inner_hash);
		}
		//Adding keys to main_hash
		for(int i=0; i<studentList.size(); i++)
		{
			key=((a*studentList.get(i).roll_no+b)%101)%25;
			main_hash.get(key).add(studentList.get(i));
		}

		//printing the roll_no. of students registered
		for(int i=0; i<main_hash.size(); i++)
		{
			for(int j=0; j<main_hash.get(i).size(); j++)
			{
				if(main_hash.get(i).get(j).roll_no!=0)
				{
				System.out.println(main_hash.get(i).get(j).roll_no);
				}
			}
		}
		
		// operations on hash table
		String c=null;
		int search=0;
		int selection;
		Scanner input = new Scanner(System.in);
		do
		{
			System.out.println("enter 1 for insertion, 2 for deletion and 3 for search");
			selection= input.nextInt();

			//loop for insertion
			if(selection==1)
			{
				int rol;
				String db,add,dep,gen;
				System.out.println("enter roll_no,dob,address,dept and gender");
				rol = input.nextInt();
				db = input.next();
				add = input.next();
				dep = input.next();
				gen = input.next();

				Student tStudent = new Student(rol,db,add,dep,gen);
				key=((a*tStudent.roll_no+b)%101)%25;
				main_hash.get(key).add(tStudent);
			}

			//loop for deletion
			if(selection==2)
			{
				search=input.nextInt();
				for(int i=0; i<main_hash.size(); i++)
				{
					for(int j=0; j<main_hash.get(i).size(); j++)
					{
						if(main_hash.get(i).get(j).roll_no==search)
						{
						main_hash.get(i).remove(j);
						}
					}
				}
			}

			//loop for search
			if(selection==3)
			{
				search=input.nextInt();
				for(int i=0; i<main_hash.size(); i++)
				{
					for(int j=0; j<main_hash.get(i).size(); j++)
					{
						if(main_hash.get(i).get(j).roll_no==search)
						{
							System.out.println("Index in main hash:" +  i + '\n' + "Index in secondary hash:" + j);
							System.out.println("dob:" + main_hash.get(i).get(j).dob);
							System.out.println("address:" + main_hash.get(i).get(j).address);
							System.out.println("dept:" + main_hash.get(i).get(j).dept);
							System.out.println("gender:" + main_hash.get(i).get(j).gender);
						}
					}
				}
			}
			System.out.println("enter y for more operations");
			c = input.next();
		}
		while(c.equals("y"));
		input.close();
		//statistics collection begins
		System.out.println("Statistics collection");
		load_factor=total/25;
		System.out.println("no. of keys: " + total);
		System.out.println("load factor: " + load_factor);
		for(int i=0; i<25; i++)
		{
			for(int j=0; j<=main_hash.get(i).size(); j++)
			{
				comparisons=comparisons + j ;
			}
		}
		avg_compare=(comparisons/studentList.size())+1;
		System.out.println("average comparisons=" + avg_compare);
	}
}