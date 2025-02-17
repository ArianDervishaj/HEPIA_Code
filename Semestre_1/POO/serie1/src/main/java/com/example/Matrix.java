package com.example;

public class Matrix {
    public static void print(double[][] mat) {
        for (int row = 0; row < mat.length; row++) {
            for (int col = 0; col < mat[0].length; col++) {
                System.out.print(mat[row][col] + "\t");
            }
            System.out.println();
        }
        System.out.println();
    }

    // Matrix multiplication method
    public static double[][] mult(double[][] mat1, double[][] mat2) {

        if (mat1[0].length != mat2.length) {
            System.out.println("Matrix multiplication is not possible.");
            return new double[0][0]; // Return empty matrix if invalid dimensions
        }
        double[][] res = new double[mat1.length][mat2[0].length];

        for (int i = 0; i < mat1.length; i++) {
            for (int j = 0; j < mat2[0].length; j++) {
                for (int k = 0; k < mat2.length; k++) {
                    res[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }
        return res;
    }

    public static double[][] add(double[][] mat1, double[][] mat2) {
        if (mat1.length != mat2.length || mat1[0].length != mat2[0].length) {
            System.out.println("Matrix addition is not possible.");
            return new double[0][0];
        }

        double[][] res = new double[mat1.length][mat1[0].length];

        for (int i = 0; i < mat1.length; i++) {
            for (int j = 0; j < mat1[0].length; j++) {
                res[i][j] = mat1[i][j] + mat2[i][j];
            }
        }

        return res;
    }
}
