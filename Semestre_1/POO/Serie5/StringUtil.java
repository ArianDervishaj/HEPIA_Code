import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class StringUtil {
    public static Map<Character, Integer> countOccurence(String str) {
        Map<Character, Integer> charCount = new HashMap<>();
        for (char c : str.toCharArray()) {
            charCount.put(c, charCount.getOrDefault(c, 0) + 1);
        }
        return charCount;
    }

    public static double avgSize(List<String> input) {
        double size = 0;
        for (String s : input) {
            size += s.length();
        }
        size /= input.size();
        return size;
    }

    public static void main(String[] args) {
        // Test Method 1
        String testString = "hellolle";
        System.out.println("Character counts: " + countOccurence(testString));

        // Test Method 2
        List<String> testList = Arrays.asList("hello", "world", "java");
        System.out.println("Average string length: " + avgSize(testList));
    }
}