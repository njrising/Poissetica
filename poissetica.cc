// Future site for thesis software  
// 
//
//
//
// To Do:
// 1. Generate and view 3d honeycombs 
// 2. 
//
//
//
// Testing... Don't compile


int main(void){



return 0;
}




// Create lattice. 
// Create_lattice([-1,1], [-1,1], [-1,1], {{1,0,0},{0,1,0},{0,0,1}}, 1)
// Create_lattice([-x, x], [-y, y], [-z, z], [basis], [lattice generation type], [max])
std::vector<float> lat;
void create_lattice(std::vector<float> &lat, int x[2], int y[2], int z[2], float bas[3][3], int gen, int max){
    for(int i = max * x[0];i <= max * x[1];++i){
        for(int j = max * y[0];j <= max * y[1];++j){
            for(int k = max * z[0];k <= max * z[1];++k){
                x = i * bas[0][0] + j * bas[1][0] + k * bas[2][0];
                y = i * bas[0][1] + j * bas[1][1] + k * bas[2][1];
                z = i * bas[0][2] + j * bas[1][2] + k * bas[2][2];    
                if(abs(x) <= max & abs(y) <= max & abs(z) <= max){
                    lat.push_back(x);
                    lat.push_back(y);
                    lat.push_back(z);
                }
            }
        }
    }
} 