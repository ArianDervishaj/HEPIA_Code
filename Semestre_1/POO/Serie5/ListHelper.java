import java.util.ArrayList;
import java.util.List;

public class ListHelper {
    public static List<Integer> doubleThat(List<Integer> is) {
        List<Integer> result = new ArrayList<>();
        for (int i : is) {
            result.add(2 * i);
        }
        return result;
    }

    public static List<Integer> filterUper(List<Integer> is, int value) {
        List<Integer> result = new ArrayList<>();
        for (int i : is) {
            if (i >= value) {
                result.add(i);
            }
        }
        return result;
    }

    public static void main(String[] argts) {
        List<Integer> test = List.of(1, 2, 3, 4, 5, 6);
        System.out.println(test);
        test = doubleThat(test);
        System.out.println(test);
        test = filterUper(test, 3);
        System.out.println(test);
    }
}