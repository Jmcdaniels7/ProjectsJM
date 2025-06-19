import java.util.*;

// O(log n) time complexity
class BinarySearch {
    boolean binarySearch(List<Integer> arr, int target)
    {
        int low = 0;
        int high = arr.size() -1;

        //how can we get the middle?
        // example {1,2,3,4,5,6}
        while( low <= high)
        {
            // the middle is technically always half of the total length
            int middle = high / 2;

            //if target is found
            if(target == arr.get(middle))
            {
                System.out.println("Found at index: " + middle);
                return true;
            }
            // if target in the right half
            else if(target > arr.get(middle))
            {
                low = middle + 1;

            }
            //if target in the left half
            else if(target > arr.get(middle))
            {
                high = middle - 1;

            }

        }
        
        return false;

    }
    
}
public class BinSearch {
    public static void main(String args[])
    {
        Integer[] nums = {9, 7, 3, 11, 23, 8, 2, 15};
        List<Integer> arr = Arrays.asList(nums);
        Collections.sort(arr);
        BinarySearch ob = new BinarySearch();
        System.out.println(ob.binarySearch(arr, 8));
    }

}
