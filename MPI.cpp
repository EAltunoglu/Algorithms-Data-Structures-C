/*
Student Name: Eren Altunoglu
Student Number: 2017400120
Compile Status: Compiling
Program Status: Working
*/
#include <cstdio>
#include <cassert>
#include <mpi.h>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

// returns manhattan distance between two instances
double manhattan_distance(const double *A, const double *B, const int size){
    double ret = 0;
    for(int i = 0; i < size; i++)
        ret += abs(A[i] - B[i]);
    return ret;
}

// diff function for relief algorithm, used to calculate W vector 
double diff(const double *A , const double *B, const int index, const double *mx, const double *mn){
    return abs(A[index] - B[index]) / (mx[index] - mn[index]);
}

int main(int argc, char* argv[]){
    
    int rank, size, limit;

    // Build MPI environment

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    FILE *input = fopen(argv[1], "r"); // input file
    int P,N,A,M,T;
    fscanf(input,"%d%d%d%d%d", &P,&N,&A,&M,&T);
    
    limit = N / (P-1); // number of instances for each slave
    
    // P -> number of processors
    // N -> number of instances
    // A -> number of features
    // M -> iteration count for weight updates
    // T -> resulting number of features. Top T features will be selected from Relief algorithm

    // All file I/O is handled with the master processor. Slave processors can only print to stdout.
    
    // If it's master processor, read from input the file
    if(rank == 0){
        int sendP = 1; // holds the slave processor
        int cnt = 0;
        double ar[A+1]; // instance features and class
        for(int i = 0; i < N; i++){
            for(int j = 0; j < A; j++)
                fscanf(input, "%lf", &ar[j]);
            fscanf(input, "%lf", &ar[A]);
            
            // send instance to slave(sendP)
            MPI_Send(
                /* data         = */ &ar,
                /* count        = */ A+1,
                /* datatype     = */ MPI_DOUBLE,
                /* destination  = */ sendP,
                /* tag          = */ cnt,
                /* communicator = */ MPI_COMM_WORLD);
            
            if(++cnt == limit){
                // send m to the slave
                MPI_Send(
                    /* data         = */ &M,
                    /* count        = */ 1,
                    /* datatype     = */ MPI_INT,
                    /* destination  = */ sendP,
                    /* tag          = */ cnt,
                    /* communicator = */ MPI_COMM_WORLD);
                // send t to the slave
                MPI_Send(
                    /* data         = */ &T,
                    /* count        = */ 1,
                    /* datatype     = */ MPI_INT,
                    /* destination  = */ sendP,
                    /* tag          = */ cnt+1,
                    /* communicator = */ MPI_COMM_WORLD);
                sendP++; // proceed to next slave
                cnt = 0;
            }
        }
        
        fclose(input);
    }

    if(rank != 0){
        double ar[limit][A+1]; // holds instances
        int m,t;
        for(int i = 0; i < limit; i++){
            // receive the instance
            MPI_Recv(
                /* data         = */ &ar[i],
                /* count        = */ A+1,
                /* datatype     = */ MPI_DOUBLE,
                /* source       = */ 0,
                /* tag          = */ i,
                /* communicator = */ MPI_COMM_WORLD,
                /* status       = */ MPI_STATUS_IGNORE);
        }
        // receive the m
        MPI_Recv(
                /* data         = */ &m,
                /* count        = */ 1,
                /* datatype     = */ MPI_INT,
                /* source       = */ 0,
                /* tag          = */ limit,
                /* communicator = */ MPI_COMM_WORLD,
                /* status       = */ MPI_STATUS_IGNORE);
        // receive the t
        MPI_Recv(
                /* data         = */ &t,
                /* count        = */ 1,
                /* datatype     = */ MPI_INT,
                /* source       = */ 0,
                /* tag          = */ limit+1,
                /* communicator = */ MPI_COMM_WORLD,
                /* status       = */ MPI_STATUS_IGNORE);
        
        // initialize W vector
        double W[A];
        for(int i = 0; i < A; i++) W[i] = 0.0;

        // select target instance
        for(int target = 0; target < m; target++){
            int hit = -1, miss = -1;
            // finds the closest hit and miss for selected instance
            // iterate over instances
            for(int i = 0; i < limit; i++){
                if(i == target) continue;
                bool type = ar[target][A] == ar[i][A]; // if ith instance's class is same with target's class it is true. otherwise false
                
                if(type){
                    if(hit == -1) hit = i;
                    else if(manhattan_distance(ar[i], ar[target], A) < manhattan_distance(ar[hit], ar[target], A))
                        hit = i;
                } else {
                    if(miss == -1) miss = i;
                    else if(manhattan_distance(ar[i], ar[target], A) < manhattan_distance(ar[miss], ar[target], A))
                        miss = i;
                }
            }
            
            // check hit and miss found
            assert(hit != -1);
            assert(miss != -1);
            
            // initialize max and min array to find max and min for each feature among received instances
            double mx[A], mn[A];
            for(int i = 0; i < A; i++)
                mx[i] = mn[i] = ar[0][i];
            
            for(int i = 1; i < limit; i++)
                for(int j = 0; j < A; j++){
                    mx[j] = max(mx[j], ar[i][j]);
                    mn[j] = min(mn[j], ar[i][j]);
                }
            
            // calculate the W vector
            for(int j = 0; j < A; j++){
                W[j] = W[j] - diff(ar[target], ar[hit], j, mx, mn)/m + diff(ar[target], ar[miss], j, mx, mn)/m;
            }
        }

        vector<pair<double, int>> v; // used to find top features
        for(int i = 0; i < A; i++)
            v.push_back(make_pair(W[i], i));
        
        sort(v.begin(), v.end()); // sort features
        reverse(v.begin(), v.end());
        
        vector<int> res;
        for(int i = 0; i < t; i++){
            res.push_back(v[i].second); // select top features
        }
        
        sort(res.begin(), res.end()); // sort top features
        
        int top_features[t];
        // print features
        printf("Slave P%d :",rank);
        for(int i = 0; i < t; i++){
            top_features[i] = res[i];
            printf(" %d",res[i]);
        }
        
        puts("");
        
        // Send top features to the master
        MPI_Send(
                    /* data         = */ &top_features,
                    /* count        = */ t,
                    /* datatype     = */ MPI_INT,
                    /* destination  = */ 0,
                    /* tag          = */ 0,
                    /* communicator = */ MPI_COMM_WORLD);
    }

    if(rank == 0){
        vector<int> ans;
        int features[T];
        for(int i = 1; i < P; i++){
            /// receive ins
            MPI_Recv(
                /* data         = */ &features,
                /* count        = */ T,
                /* datatype     = */ MPI_INT,
                /* source       = */ i,
                /* tag          = */ 0,
                /* communicator = */ MPI_COMM_WORLD,
                /* status       = */ MPI_STATUS_IGNORE);
            for(int j = 0; j < T; j++)
                ans.push_back(features[j]);
        }
        sort(ans.begin(), ans.end()); // sort all top features
        ans.resize(unique(ans.begin(), ans.end()) - ans.begin()); // remove replicas of features
        printf("Master P%d :",rank);
        for(int i = 0; i < ans.size(); i++)
            printf(" %d",ans[i]);
    }

    MPI_Finalize();

    return 0;
}

