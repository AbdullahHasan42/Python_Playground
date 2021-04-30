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
    
    double x[arr_size][2],y[arr_size];
    
    //Input x-values
    cout << "\nEnter the x-axis values:\n";                
    for (j=0;j<2;j++)
    {
        for (i=0;i<arr_size;i++)
        {
            cout << "Element x[" << i << "," << j << "] = ";
            cin >> x[i][j];
        } 
    }

    //Input y-values
    cout<<"\nEnter the y-axis values:\n";                
    for (i=0;i<arr_size;i++)
    {
        cin >> y[i];
    }
    
    //Double that will store the values of sigma(y_i)
    double sigma_Y1 = 0.0;    
    for (i=0;i<arr_size;i++)
    {
        sigma_Y1 = sigma_Y1 + y[i];
    }

    //Double that will store the values of sigma(x1_i)
    double sigma_X1 = 0.0;    
    for (i=0;i<arr_size;i++)
    {
        j = 0; //First column for X1
        sigma_X1 = sigma_X1 + x[i][j];
    }

    //Double that will store the values of sigma(x2_i)
    double sigma_X2 = 0.0;
    for (i=0;i<arr_size;i++)
    {
        j = 1; //Second column for X2
        sigma_X2 = sigma_X2 + x[i][j];
    }

    //Double that will store the values of sigma(x1^2_i)
    double sigma_sqr_X1 = 0.0;
    for (i=0;i<arr_size;i++)
    {
        j = 0; //First column for X1
        sigma_sqr_X1 = sigma_sqr_X1 + pow(x[i][j],2);
    }
    
    //Double that will store the values of sigma(x2^2_i)
    double sigma_sqr_X2 = 0.0;
    for (i=0;i<arr_size;i++)
    {
        j = 1; //Second column for X2
        sigma_sqr_X2 = sigma_sqr_X2 + pow(x[i][j],2);
    }

    //Double that will store the values of sigma(x1_i * x2_i)
    double sigma_X1dotX2 = 0.0;
    j = 0;
    for (i=0;i<arr_size;i++)
    {
        sigma_X1dotX2 = sigma_X1dotX2 + (x[i][j] * x[i][j+1]);
    }

    //Double that will store the values of sigma(x1_i * y_i)
    double sigma_X1dotY = 0.0;
    j = 0;
    for (i=0;i<arr_size;i++)
    {
        sigma_X1dotY = sigma_X1dotY + (x[i][j] * y[i]);
    }

    //Double that will store the values of sigma(x2_i * y_i)
    double sigma_X2dotY = 0.0;
    j = 1;
    for (i=0;i<arr_size;i++)
    {
        sigma_X2dotY = sigma_X2dotY + (x[i][j] * y[i]);
    }

    //B is the Normal matrix(augmented) that will store the equations
    //'coeff' is for value of the final coefficients
    double B[3][4], coeff[1];
    
    //Build the Normal matrix by storing the corresponding values at the right positions
    B[0][0] = arr_size;
    B[0][1] = sigma_X1;
    B[0][2] = sigma_X2;
    B[1][0] = sigma_X1;
    B[1][1] = sigma_sqr_X1;
    B[1][2] = sigma_X1dotX2;
    B[2][0] = sigma_X2;
    B[2][1] = sigma_X1dotX2;
    B[2][2] = sigma_sqr_X2;
    B[0][3] = sigma_Y1;
    B[1][3] = sigma_X1dotY;
    B[2][3] = sigma_X2dotY;
    
    cout<<"\nThe Normal(Augmented Matrix) is as follows:\n";    
    for (i=0;i<3;i++)            //print the Normal-augmented matrix
    {
        for (j=0;j<=3;j++)
            cout<<B[i][j]<<setw(16);
        cout<<"\n";
    }
    
    // Gaussian Elimination
    // Perform Partial Pivoting
    for (i=0;i<3;i++)
    {
        for (k=i+1;k<3;k++)
            if (B[i][i]<B[k][i])
                for (j=0;j<=3;j++)
                {
                    double temp=B[i][j];
                    B[i][j]=B[k][j];
                    B[k][j]=temp;
                }
    }
    
    // Loop to perform the gauss elimination
    // Make the elements below the pivot elements equal to zero
    for (i=0;i<2;i++){
        for (k=i+1;k<3;k++)
            {
                double t=B[k][i]/B[i][i];
                for (j=0;j<=3;j++)
                    B[k][j]=B[k][j]-t*B[i][j];  
            }
    }
    
    // Back-Substitution
    // [1] Make the variable to be calculated equal to the rhs of the last equation
    // [2] Then subtract all the lhs values except the coefficient of the variable whose value is being calculated
    // [3] Finally divide the rhs by the coefficient of the variable to be calculated
    for (i=2;i>=0;i--)
    {
        coeff[i]=B[i][3];                           // [1]
        for (j=0;j<3;j++)
            if (j!=i)
                coeff[i]=coeff[i]-B[i][j]*coeff[j]; // [2]
        coeff[i]=coeff[i]/B[i][i];                  // [3]
    }

    cout<<"\nThe values of the coefficients are as follows:\n";
    
    for (i=0;i<3;i++)
    {
        // Print the values of a0, x_1, x_2
        // if (coeff[i] != 0)
            cout<<"x^"<<i<<"="<<coeff[i]<<endl;
    }
    
    cout << "\nHence the fitted Polynomial is given by:\ny=";
    
    for (i=0;i<3;++i)
    {
        // if (coeff[i] != 0)
            cout << " + (" << coeff[i] << ")" << "x_" << i;
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

                double x_p[p_arr_size][p_arr_size];
                double y_p[p_arr_size];
                double temp = 0.0;

                //Input x-values
                cout << "\nEnter the x-axis values:\n";                
                for (j=0;j<2;j++)
                {
                    for (i=0;i<p_arr_size;i++)
                    {
                        cout << "Element x[" << i << "," << j << "] = ";
                        cin >> x_p[i][j];
                    } 
                }

                // Clearing trash values pre-set before calculating
                y_p[j] = 0.0;
                
                for (j=0;j<p_arr_size;j++)
                {
                    temp = coeff[0] + (coeff[1] * x_p[j][0]) + (coeff[2] * x_p[j][1]);
                    y_p[j] = temp;

                    cout<< "\nPrediction at ["<< x_p[j][0] << ", " << x_p[j][1] << "] = " << y_p[j] << endl;
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