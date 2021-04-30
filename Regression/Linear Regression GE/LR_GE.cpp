#include<iostream>
#include<iomanip>
#include<cmath>

using namespace std;


int main()
{
    int i,j,k,m,arr_size;
    
    //set precision
    cout.precision(2);
    cout.setf(ios::fixed);
    
    //To find the size of arrays that will store x, y, and z values
    cout << "\nEnter the no. of data pairs to be entered:\n";
    cin >> arr_size;
    
    double x[arr_size],y[arr_size];
    
    //Input x-values
    cout << "\nEnter the x-axis values:\n";                
    for (i=0;i<arr_size;i++)
    {
        cin >> x[i];
    }

    //Input y-values
    cout<<"\nEnter the y-axis values:\n";                
    for (i=0;i<arr_size;i++)
    {
        cin >> y[i];
    }

    cout << "\nWhat degree of Polynomial do you want to use for the fit?\n";
    // m is the degree of Polynomial
    cin >> m;
    
    //Array that will store the values of sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
    double X[2*m+1];
    
    //consecutive positions of the array will store n,sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
    for (i=0;i<2*m+1;i++)
    {
        X[i]=0;
        for (j=0;j<arr_size;j++)
            X[i] = X[i] + pow(x[j],i);
            /// cout << X[i] << setw(16);
    }
    
    //B is the Normal matrix(augmented) that will store the equations
    //'coeff' is for value of the final coefficients
    double B[m+1][m+2], coeff[m+1];
    
    //Build the Normal matrix by storing the corresponding coefficients
    //at the right positions except the last column of the matrix
    for (i=0;i<=m;i++)
    {
        for (j=0;j<=m;j++)
            B[i][j]=X[i+j];
    }
    
    //Array to store the values of sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^m*yi)
    double Y[m+1];
    
    //consecutive positions will store sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^m*yi)
    for (i=0;i<m+1;i++)
    {    
        Y[i]=0;
        for (j=0;j<arr_size;j++)
            Y[i]=Y[i]+pow(x[j],i)*y[j];
    }
    
    //load the values of Y as the last column of B(Normal Matrix but augmented)
    for (i=0;i<=m;i++)
    {
        B[i][m+1]=Y[i];
    }
    
    // m is made m + 1 because the Gaussian Elimination part below was for m equations,
    // but here m is the degree of polynomial and for m degree we get m+1 equations
    m = m + 1;
    
    cout<<"\nThe Normal(Augmented Matrix) is as follows:\n";    
    for (i=0;i<m;i++)            //print the Normal-augmented matrix
    {
        for (j=0;j<=m;j++)
            cout<<B[i][j]<<setw(16);
        cout<<"\n";
    }
    
    // Gaussian Elimination
    // Perform Partial Pivoting
    for (i=0;i<m;i++)
    {
        for (k=i+1;k<m;k++)
            if (B[i][i]<B[k][i])
                for (j=0;j<=m;j++)
                {
                    double temp=B[i][j];
                    B[i][j]=B[k][j];
                    B[k][j]=temp;
                }
    } 
    
    // Loop to perform the gauss elimination
    // Make the elements below the pivot elements equal to zero
    for (i=0;i<m-1;i++){
        for (k=i+1;k<m;k++)
            {
                double t=B[k][i]/B[i][i];
                for (j=0;j<=m;j++)
                    B[k][j]=B[k][j]-t*B[i][j];
            }
    }
    
    // Back-Substitution
    // [1] Make the variable to be calculated equal to the rhs of the last equation
    // [2] Then subtract all the lhs values except the coefficient of the variable whose value is being calculated
    // [3] Finally divide the rhs by the coefficient of the variable to be calculated
    for (i=m-1;i>=0;i--)
    {
        coeff[i]=B[i][m];                           // [1]
        for (j=0;j<m;j++)
            if (j!=i)                   
                coeff[i]=coeff[i]-B[i][j]*coeff[j]; // [2]
        coeff[i]=coeff[i]/B[i][i];                  // [3]
    }

    cout<<"\nThe values of the coefficients are as follows:\n";
    
    for (i=0;i<m;i++)
    {
        // Print the values of x^0,x^1,x^2,x^3,..
        // if (coeff[i] != 0)
            cout<<"x^"<<i<<"="<<coeff[i]<<endl;
    }
    
    cout << "\nHence the fitted Polynomial is given by:\ny=";
    
    for (i=0;i<m;++i)
    {
        // if (coeff[i] != 0)
            cout << " + (" << coeff[i] << ")" << "x^" << i;
    }
    
    cout << "\n";
    
    char answer;
    bool flag = true;

    while (flag)
    {
        cout << "\nDo you want to predict values? (y/n): ";
        cin >> answer;

        switch(answer)
        {
            case 'y':
            {
                int p_arr_size;
                cout << "\nEnter the no. of data pairs to be entered:\n";
                cin >> p_arr_size;

                double x_p[p_arr_size];
                double y_p[p_arr_size];
                double temp = 0.0;

                cout << "\nEnter the x-axis values:\n";                
                for (j=0;j<p_arr_size;j++)
                {
                    cin >> x_p[j];
                }

                for (j=0;j<p_arr_size;j++)
                {
                    // Clearing trash values pre-set before calculating
                    y_p[j] = 0.0;

                    for (i=0;i<m;i++)
                    {
                        temp = coeff[i] * pow(x_p[j],i);
                        y_p[j] = y_p[j] + temp;
                    }
                }

                for (j=0;j<p_arr_size;j++)
                {   
                    cout<< "\nPrediction at "<< x_p[j] << " = " << y_p[j] << endl;
                }

                break;
            }

            case 'n':
            {
                flag = false;
                break;
            }

            default: cout << "Enter 'y' for prediction and 'n' for application exit" << endl;
        }
    }

    return 0;
}