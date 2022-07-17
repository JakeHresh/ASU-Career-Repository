import java.util.Scanner;
public class Company
{
    static Scanner scan = new Scanner(System.in);
    public static void main(String[] args)
    {
        Employee[] empArr = new Employee[5];
        AdministrativeAssistant[] hourlyEmpArr = new  AdministrativeAssistant[5];
        String input = mainMenu();
        while(!input.equals("F"))
        {
            if(input.equals("A"))
            {
                if(empArr[0] != null && empArr[1] != null && empArr[2] != null && empArr[3] != null && empArr[4] != null)
                {
                    System.out.println("Error. Cannot add more employees.");
                }
                for(int i = 0; i < empArr.length; i++)
                {
                    if(empArr[i] == null)
                    {
                        System.out.println("What is their name?");
                        String empName = scan.nextLine();
                        System.out.println("What is their salary (yearly or hourly)?");
                        double empSal = scan.nextDouble();
                        System.out.println("Are they an hourly worker? (Y/N)");
                        scan.nextLine();
                        String yesNo = scan.nextLine();
                        yesNo = yesNo.toUpperCase();
                        if(yesNo.equals("Y"))
                        {
                            System.out.println("How many hours per week do they work?");
                            int hours = scan.nextInt();
                            empArr[i] = new AdministrativeAssistant(empName, empSal, hours);
                            for(int j = 0; j < hourlyEmpArr.length; j++)
                            {
                                if(hourlyEmpArr[j] == null)
                                {
                                    hourlyEmpArr[j] = new AdministrativeAssistant(empName, empSal, hours);
                                    j = hourlyEmpArr.length;
                                }
                            }
                            System.out.println(empName + " was hired!");
                            scan.nextLine();
                            i = empArr.length;
                        }
                        else if(yesNo.equals("N"))
                        {
                            empArr[i] = new SoftwareEngineer(empName, empSal);
                            System.out.println(empName + " was hired!");
                            i = empArr.length;
                        }
                    }
                }
            }
            else if(input.equals("B"))
            {
                if(empArr[0] == null)
                {
                    System.out.println("Nobody works here!");
                }
                for(int i = 0; i < empArr.length; i++)
                {
                    if(empArr[i] != null)
                    {
                        Employee employee = empArr[i];
                        String softOrAdmin = " Software Engineer";
                        String salOrWage = " Salary: ";
                            for(int j = 0; j < hourlyEmpArr.length; j++)
                            {
                                if(hourlyEmpArr[j] != null)
                                {
                                    if(employee.getClass() == hourlyEmpArr[j].getClass() && employee.getName().equals(hourlyEmpArr[j].getName()))
                                    {
                                        salOrWage = " Hourly Wage: ";
                                        softOrAdmin = " Administrative Assistant";
                                        j = hourlyEmpArr.length;
                                    }
                                }
                            }
                        String list = employee.getName() + salOrWage + employee.getSalary() + " Cash: " + employee.getCash() + softOrAdmin;
                        System.out.println(list);
                    }
                }
            }
            else if(input.equals("C"))
            {
                System.out.println("To whom do you want to give a raise?");
                String name = scan.nextLine();
                boolean isName = false;
                for(int i = 0; i < empArr.length; i++)
                {
                    if(empArr[i] != null && empArr[i].getName().equals(name))
                    {
                        System.out.println("What raise do you want to give them?");
                        double percent = scan.nextDouble();
                        scan.nextLine();
                        System.out.println(name + " is happy!");
                        empArr[i].giveRaise(percent);
                        isName = true;
                        i = empArr.length;
                    }
                }
                if(isName != true)
                {
                    System.out.println("Error. Name not found.");
                
                }
            }
                else if(input.equals("D"))
                {
                    boolean wasPaid = false;
                    for(int i = 0; i < empArr.length; i++)
                    {
                        if(empArr[i] != null)
                        {
                            wasPaid = true;
                            empArr[i].getPaid();
                        }
                    }
                    if(wasPaid == true)
                    {
                        System.out.println("Hooray for money!");
                    }
                    else
                    {
                        System.out.println("Error. No employees to pay.");
                    }
                }
            else if(input.equals("E"))
            {
                boolean isHourlyEmp = false;
                System.out.println("Change hours for whom?");
                String name2 = scan.nextLine();
                for(int i = 0; i < hourlyEmpArr.length; i++)
                {
                    if(hourlyEmpArr[i] != null && hourlyEmpArr[i].getName().equals(name2))
                    {
                        isHourlyEmp = true;
                        System.out.println(name2 + " currently works " + hourlyEmpArr[i].numHours() + " hours per week. What would you like to change it to?");
                        int changeHours = scan.nextInt();
                        scan.nextLine();
                        System.out.println(name2 + " will now work " + changeHours + " hours per week.");
                        hourlyEmpArr[i].changeHours(changeHours);
                        i = hourlyEmpArr.length;
                    }
                }
                if(isHourlyEmp != true)
                {
                    System.out.println("Error. Hourly employee not found.");
                }
            }
            input = mainMenu();
        }
        System.out.println("Bye!");
        scan.close();
    }
    
    public static String mainMenu()
    {
        System.out.println("What do you want to do?");
        System.out.println("A. Add an Employee");
        System.out.println("B. List All Employees");
        System.out.println("C. Give an Employee a Raise");
        System.out.println("D. Give Paychecks");
        System.out.println("E. Change Someone's Hours");
        System.out.println("F. Quit");
        String input = scan.nextLine();
        input = input.toUpperCase();
        while(!input.equals("A") && !input.equals("B") && !input.equals("C") && !input.equals("D") && !input.equals("E") && !input.equals("F"))
        {
            System.out.println("Invalid option");
            input = scan.nextLine();
            input = input.toUpperCase();
        }
        return input;
    }
}
