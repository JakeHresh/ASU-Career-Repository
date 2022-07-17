import java.util.Scanner;
public class Assignment1
{
    static Scanner scan = new Scanner(System.in);
    public static void main(String[] args)
    {
        Shelf[] shelfArray = {new Shelf(), new Shelf(), new Shelf()};
        System.out.println("What do you want to do?");
        String input = mainMenu();
        while(!input.equals("E"))
        {
            if(input.equals("A"))
            {
                Item item = addItem();
                boolean itemAdded = false;
                for(int i = 0; i < shelfArray.length; i++)
                {
                    itemAdded = shelfArray[i].addItem(item);
                    if(itemAdded == true)
                    {
                        System.out.println(item.getName() + " was added to Shelf " + (i + 1));
                        i = shelfArray.length;
                    }
                }
                if(itemAdded == false)
                {
                    System.out.println("Sorry. All the Shelves are full.");
                }
            }
            else if(input.equals("B"))
            {
                for(int i = 0; i < shelfArray.length; i++)
                {
                    String[] nameList = shelfArray[i].itemNameList();
                    if(nameList.length > 0)
                    {
                        System.out.print("Shelf " + (i + 1) + " " + nameList[0]);
                    }
                    for(int j = 1; j < nameList.length; j++)
                    {
                        System.out.print(", " + nameList[j]);
                    }
                    if(shelfArray[i].itemArray[0] == null && shelfArray[i].itemArray[1] == null && shelfArray[i].itemArray[2] == null && shelfArray[i].itemArray[3] == null && shelfArray[i].itemArray[4] == null)
                    {
                        System.out.println("Shelf " + (i + 1) + " is empty");
                    }
                    System.out.println();
                }
            }
            else if(input.equals("C"))
            {
                System.out.println("Please enter the name of the Item");
                double price = 0;
                String itemName = scan.nextLine();
                for(int i = 0; i < shelfArray.length; i++)
                {
                    price = shelfArray[i].priceCheck(itemName);
                    if(price > -1)
                    {
                        System.out.println(itemName + " is worth $" + (price/100));
                        i = shelfArray.length;
                    }
                }
                if(price < 0)
                {
                    System.out.println(itemName + " could not be found!");
                }
            }
            else if(input.equals("D"))
            {
                System.out.println("Please enter the name of the Item to remove");
                String itemName = scan.nextLine();
                boolean removed = false;
                for(int i = 0; i < shelfArray.length; i++)
                {
                    removed = shelfArray[i].itemRemove(itemName);
                    if(removed == true)
                    {
                        System.out.println(itemName + " was removed from Shelf " + (i + 1));
                        i = shelfArray.length;
                    }
                }
                if(removed == false)
                {
                    System.out.println(itemName + " could not be found!");
                }
            }
            System.out.println("What do you want to do?");
            input = mainMenu();
        }
        System.out.println("Bye");
        scan.close();
    }
    
    public static String mainMenu()
    {
        System.out.println("A. Add an Item");
        System.out.println("B. List all Items");
        System.out.println("C. Check the value of an Item");
        System.out.println("D. Remove an Item");
        System.out.println("E. Quit");
        String input = scan.nextLine();
        input = input.toUpperCase();
        while(!input.equals("A") && !input.equals("B") && !input.equals("C") && !input.equals("D") && !input.equals("E"))
        {
            System.out.println("Invalid option");
            input = scan.nextLine();
            input = input.toUpperCase();
        }
        return input;
    }
    
    public static Item addItem()
    {
        System.out.println("What is the Item called?");
        String itemName = scan.nextLine();
        System.out.println("What is its value in cents?");
        double value = scan.nextDouble();
        while(value < 0)
        {
            System.out.println("Please enter a valid value");
            value = scan.nextDouble();
        }
        scan.nextLine();
        Item item = new Item(itemName, value);
        return item;
    }
}
