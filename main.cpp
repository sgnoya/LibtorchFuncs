#include <torch/script.h>
#include <torch/torch.h>

using namespace std;
using namespace torch;

// Prototype declarations 
Tensor cpp_matmul(Tensor x, Tensor y);
vector<Tensor> cpp_matsmul(vector<Tensor> x, vector<Tensor> y);

// Register the cpp functions to dll.
static auto registry =
	RegisterOperators("sample::matmul", &cpp_matmul)
		.op("sample::matsmul", &cpp_matsmul);


// CPP functions
Tensor cpp_matmul(Tensor x, Tensor y)
{
	return x.matmul(y);
}

vector<Tensor> cpp_matsmul(vector<Tensor> x, vector<Tensor> y)
{
	vector<Tensor> z;

	if (x.size() != y.size()) {
		cerr << "The numbers of tensors must be the same." << endl;
		return z;
	}

	for (int i = 0; i < x.size(); i++) {
		z.push_back(x[i].matmul(y[i]));
	}
	return z;
}
