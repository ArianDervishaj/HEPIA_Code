package com.example;

public class Vector {

    public double[] add(double[] vec1, double[] vec2) {
        if (vec1.length != vec2.length) {
            return new double[0];
        }

        int size = vec1.length;
        double[] res = new double[size];

        for (int i = 0; i < size; i++) {
            res[i] = vec1[i] + vec2[i];
        }

        return res;
    }

    public double[] mul(double[] vec, int scal) {
        if (vec == null || vec.length == 0) {
            return new double[0];
        }

        double[] res = new double[vec.length];
        for (int i = 0; i < vec.length; i++) {
            res[i] = vec[i] * scal;
        }

        return res;
    }

    public double[] sub(double[] vec1, double[] vec2) {
        if (vec1.length != vec2.length) {
            return new double[0];
        }

        double[] res = add(vec1, mul(vec2, -1));
        return res;
    }

    public int len(double[] vec) {
        if (vec == null) {
            return 0;
        }

        return vec.length;
    }

    public double norm(double[] vec) {
        if (vec == null || vec.length == 0) {
            return 0;
        }

        double res = 0;
        for (int i = 0; i < vec.length; i++) {
            res += Math.pow(vec[i], 2);
        }
        return Math.sqrt(res);
    }

    public double[] sum(double[][] list_vec) {
        if (list_vec.length == 0 || list_vec[0].length == 0) {
            return new double[0];
        }

        int size = list_vec[0].length;
        double[] res = new double[size];

        for (double[] vec : list_vec) {
            if (vec.length != size) {
                return new double[0];
            }
            res = add(res, vec);
        }
        return res;
    }

    public double norms(double[][] list_vec) {
        double[] sum = sum(list_vec);
        return norm(sum);
    }

    public double[][] concat(double[] vec1, double[] vec2) {
        if (vec1.length != vec2.length) {
            return new double[0][0];
        }

        double[][] res = new double[2][vec1.length];
        for (int i = 0; i < vec1.length; i++) {
            res[0][i] = vec1[i];
            res[1][i] = vec2[i];
        }
        return res;
    }

    public double[] sliceFrom(double[] vec1, int index) {
        if (index < 0 || index >= vec1.length) {
            return new double[0];
        }

        double[] res = new double[vec1.length - index];
        for (int i = 0; i < res.length; i++) {
            res[i] = vec1[index + i];
        }
        return res;
    }

    public double[] slice(double[] vec1, int startIndex, int endIndex) {
        if (startIndex < 0 || endIndex > vec1.length || startIndex > endIndex) {
            return new double[0];
        }

        double[] res = new double[endIndex - startIndex];
        for (int i = 0; i < res.length; i++) {
            res[i] = vec1[startIndex + i];
        }
        return res;
    }
}
