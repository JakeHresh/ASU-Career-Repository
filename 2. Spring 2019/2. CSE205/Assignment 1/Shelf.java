public class Shelf
{
    final int MAX_ITEM_NUM = 5;
    public Item[] itemArray = new Item[MAX_ITEM_NUM];
    
    public Shelf()
    {
        itemArray[0] = null;
        itemArray[1] = null;
        itemArray[2] = null;
        itemArray[3] = null;
        itemArray[4] = null;
    }
    
    public boolean addItem(Item item)
    {
        boolean added = false;
        for(int i = 0; i < itemArray.length; i++)
        {
            if(itemArray[i] == null)
            {
                itemArray[i] = item;
                added = true;
                i = itemArray.length;
            }
        }
        return added;
    }
    
    public String[] itemNameList()
    {
        String[] nameList = new String[MAX_ITEM_NUM];
        String[] copy;
        int counter = 0;
        int counter2 = 0;
        for(int i = 0; i < nameList.length; i++)
        {
            if(itemArray[i] != null)
            {
                nameList[i - counter] = itemArray[i].getName();
            }
            else
            {
                counter++;
            }
        }
        copy = new String[MAX_ITEM_NUM - counter];
        for(int i = 0; i < copy.length; i++)
        {
            if(nameList[i] != null)
            {
                copy[i - counter2] = nameList[i];
            }
            else
            {
                counter2++;
            }
        }
        return copy;
    }
    
    public double priceCheck(String s)
    {
        double price = -1;
        for(int i = 0; i < itemArray.length; i++)
        {
            if(itemArray[i] != null)
            {
                if(s.equals(itemArray[i].getName()))
                {
                    price = itemArray[i].getValue();
                    i = itemArray.length;
                }
            }
        }
        return price;
    }
    
    public boolean itemRemove(String s)
    {
        boolean itemRemoved = false;
        for(int i = 0; i < itemArray.length; i++)
        {
            if(itemArray[i] != null)
            {
                if(s.equals(itemArray[i].getName()))
                {
                    itemArray[i] = null;
                    itemRemoved = true;
                    i = itemArray.length;
                }
            }
        }
        return itemRemoved;
    }
}
