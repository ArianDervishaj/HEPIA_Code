package com.example;

import java.util.Arrays;
import java.util.Scanner;

public class App {
    public static void ex11() {
        Vector vector = new Vector();

        double[] vec1 = new double[] { 1.0, 3.0, 65.0, 5.0 };
        double[] vec2 = new double[] { 1.0, 3.0, 5.0, 4.0 };
        double[] vec3 = new double[] { 4.0, 1.0, 10.0, 2.0 };

        double[][] list = { vec1, vec2, vec3 };
        int scal = 4;

        // Addition
        double[] res = vector.add(vec1, vec2);
        System.out.println("Addition:");
        System.out.println("  " + Arrays.toString(vec1));
        System.out.println("+ " + Arrays.toString(vec2));
        System.out.println("= " + Arrays.toString(res));
        System.out.println();

        // Multiplication by scalar
        res = vector.mul(vec1, scal);
        System.out.println("Multiplication by scalar:");
        System.out.println("  " + Arrays.toString(vec1));
        System.out.println("* " + scal);
        System.out.println("= " + Arrays.toString(res));
        System.out.println();

        // Subtraction
        res = vector.sub(vec1, vec2);
        System.out.println("Subtraction:");
        System.out.println("  " + Arrays.toString(vec1));
        System.out.println("- " + Arrays.toString(vec2));
        System.out.println("= " + Arrays.toString(res));
        System.out.println();

        // Length
        double res1 = vector.len(vec1);
        System.out.println("Length:");
        System.out.println("  " + Arrays.toString(vec1));
        System.out.println("len : " + res1);
        System.out.println();

        // Norm
        res1 = vector.norm(vec1);
        System.out.println("Norm:");
        System.out.println("  " + Arrays.toString(vec1));
        System.out.println("= " + res1);
        System.out.println();

        // Sum
        res = vector.sum(list);
        System.out.println("Sum:");
        System.out.println("  " + Arrays.toString(vec1));
        System.out.println("+ " + Arrays.toString(vec2));
        System.out.println("+ " + Arrays.toString(vec3));
        System.out.println("= " + Arrays.toString(res));
        System.out.println();

        // Norms of list
        res1 = vector.norms(list);
        System.out.println("Norms:");
        System.out.println("  " + Arrays.toString(vec1));
        System.out.println("  " + Arrays.toString(vec2));
        System.out.println("  " + Arrays.toString(vec3));
        System.out.println("= " + res1);
        System.out.println();

        // Concatenation
        double[][] res3 = vector.concat(vec1, vec2);
        System.out.println("Concatenation:");
        System.out.println("  " + Arrays.toString(vec1));
        System.out.println("  " + Arrays.toString(vec2));
        System.out.println("= [");
        System.out.println("  " + Arrays.toString(res3[0]));
        System.out.println("  " + Arrays.toString(res3[1]));
        System.out.println("]");

        // Slice from
        int index = 2;
        double[] slicedResFrom = vector.sliceFrom(vec1, index);
        System.out.println("Slice from index " + index + ":");
        System.out.println("  " + Arrays.toString(vec1));
        System.out.println("Slice starting from index " + index + ": " + Arrays.toString(slicedResFrom));
        System.out.println();

        // Slice between
        int startIndex = 1;
        int endIndex = 3;
        double[] slicedRes = vector.slice(vec1, startIndex, endIndex);
        System.out.println("Slice between index " + startIndex + " and " + endIndex + ":");
        System.out.println("  " + Arrays.toString(vec1));
        System.out.println("Slice from index " + startIndex + " to " + endIndex + ": " + Arrays.toString(slicedRes));
        System.out.println();

    }

    public static void ex12() {
        double[][] mat1 = { { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } };
        double[][] mat2 = { { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }, { 7.0, 8.0, 9.0 } };

        double[][] mul = Matrix.mult(mat1, mat2);
        Matrix.print(mat1);
        System.out.println("*");
        Matrix.print(mat2);
        System.out.println("=");
        Matrix.print(mul);

        double[][] add = Matrix.add(mat1, mat2);
        Matrix.print(mat1);
        System.out.println("+");
        Matrix.print(mat2);
        System.out.println("=");
        Matrix.print(add);
    }

    public static int countPositive(double[][] array) {
        int count = 0;
        for (double[] row : array) {
            for (double value : row) {
                if (value > 0) {
                    count++;
                }
            }
        }
        return count;
    }

    public static void ex13() {
        double[][] example = {
                { 1.0, -2.0 },
                { 3.0 },
                { 1.5, -2.5, 3.0 }
        };

        int res = countPositive(example);
        System.out.println("Count:" + res);
    }

    public static boolean isNumeric(String term) {
        term = term.trim();
        if (term.isEmpty()) {
            return false;
        }
        for (int i = 0; i < term.length(); i++) {
            if (i == 0 && (term.charAt(i) == '-' || term.charAt(i) == '+')) {
                continue;
            }
            if (!Character.isDigit(term.charAt(i))) {
                return false;
            }
        }
        return true;
    }

    public static int[] indexes(String term, char c) {
        java.util.ArrayList<Integer> indexList = new java.util.ArrayList<>();
        for (int i = 0; i < term.length(); i++) {
            if (term.charAt(i) == c) {
                indexList.add(i);
            }
        }
        int[] result = new int[indexList.size()];
        for (int i = 0; i < result.length; i++) {
            result[i] = indexList.get(i);
        }
        return result;
    }

    public static void ex14() {
        System.out.println(isNumeric("42"));
        System.out.println(isNumeric(" 22 "));
        System.out.println(isNumeric("-33   "));
        System.out.println(isNumeric("22.0"));
        System.out.println(isNumeric("2f3"));

        int[] indexes = indexes("maison", 'i');
        for (int index : indexes) {
            System.out.print(index + " ");
        }
    }

    public static void main(String[] args) {
        // ex11();
        // ex12();
        // ex13();
        // ex14();
    }
}
