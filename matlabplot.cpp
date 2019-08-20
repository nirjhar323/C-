//Code to implement MATLAB plots during C++ program runtime using engine.h and mex.h files.

//Comile Command: g++ -g -std=c++11 -I D:\MATLAB\extern\include matlabplot.cpp -o matlabplot

#include <iostream>
#include <vector>
#include "engine.h"
#include "mex.h"

// create mxArray matrix from an array of data
mxArray* data_to_mxarray(const double *data, int nrows, int ncols)
{
    mxArray *arr = mxCreateDoubleMatrix(nrows, ncols, mxREAL);
    double *x = mxGetPr(arr);
    for (int c=0; c<ncols; c++) {
        for (int r=0; r<nrows; r++) {
            *x = data[r + c*nrows];
            x++;
        }
    }
    return arr;
}

int main()
{
    // step 1: some data
    const char *fieldnames[2] = {"z1", "z2"};
    double z1[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    double z2[] = {7.0, 8.0, 9.0, 0.0, 1.0, 2.0};

    // open connection to MATLAB
    Engine *ep = engOpen("");

    // create structure with desired fields
    mxArray *st = mxCreateStructMatrix(1, 1, 2, fieldnames);
    mxSetField(st, 0, "z1", data_to_mxarray(z1,2,3));
    mxSetField(st, 0, "z2", data_to_mxarray(z2,3,2));

    // step 2: pass struct to MATLAB workspace
    engPutVariable(ep, "st", st);

    // for the sake of this example, lets create a fake function
    engEvalString(ep, "my_function = @(x) magic(3);");

    // step 3: call some function with the struct as input
    engEvalString(ep, "out = my_function(st);");

    // step 4: retrieve function output
    mxArray *out = engGetVariable(ep, "out");

    // extract data out of it. This depends on the type of output.
    // Say the result was a numeric array
    double *x = mxGetPr(out);
    size_t len = mxGetNumberOfElements(out);
    std::vector<double> v;
    v.resize(len);
    v.assign(x, x+len);
    for (int i=0; i<v.size(); i++) {
        std::cout << v[i] << std::endl;
    }

    // cleanup
    mxDestroyArray(out);
    mxDestroyArray(st);
    engClose(ep);

    return 0;
}
