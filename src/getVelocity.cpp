
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdio.h>
#include <io.h>
#include <sstream>

//#include <vtkVersion.h>
//#include <vtkCellArray.h>
//#include <vtkCellTypes.h>
//#include <vtkDataArray.h>
//#include <vtkDataSet.h>
//#include <vtkFloatArray.h>
//#include <vtkDoubleArray.h>
//#include <vtkPoints.h>
//#include <vtkGenericDataArray.h>

//#include <vtkPointData.h>
//#include <vtkPointDataToCellData.h>
//#include <vtkPolyData.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkXMLImageDataWriter.h>

#include <vtkImageData.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkVector.h>
using namespace std;


string int2str(int i)
{
	string str;
	stringstream ss;
	ss<<i;
	str = ss.str();
	return str;
}
vector<int> *InputData_To_Vector(string s)
{
	vector<int> *p = new vector<int>;
	ifstream infiles (s);
	int number;
	while(!infiles.eof())
	{
		infiles>>number;
		p->push_back(number);
	}
	p->pop_back();//此处要将最后一个数字弹出，是因为上述循环将最后一个数字读取了两次
	return p;
}//type is int
vector<float> *InputData_To_Vector_Float(string s)
{
	vector<float> *p = new vector<float>;
	ifstream infiles (s);
	float number;
	while(!infiles.eof())
	{
		infiles>>number;
		p->push_back(number);
	}
	p->pop_back();//此处要将最后一个数字弹出，是因为上述循环将最后一个数字读取了两次
	return p;
}
vector<double> *InputData_To_Vector_Double(string s)
{
	vector<double> *p = new vector<double>;
	ifstream infiles(s);
	double number;
	while (!infiles.eof())
	{
		infiles >> number;
		p->push_back(number);
	}
	p->pop_back();//此处要将最后一个数字弹出，是因为上述循环将最后一个数字读取了两次
	return p;
}
void getFiles( string path, string exd, vector<string>& files )
{
    //文件句柄
    long   hFile   =   0;
    //文件信息
    struct _finddata_t fileinfo;
    string pathName, exdName;

    if (0 != strcmp(exd.c_str(), ""))
    {
        exdName = "\\*." + exd;
    }
    else
    {
        exdName = "\\*";
    }

    if((hFile = _findfirst(pathName.assign(path).append(exdName).c_str(),&fileinfo)) !=  -1)
    {
        do
        {
            //如果是文件夹中仍有文件夹,迭代之
            //如果不是,加入列表
            if((fileinfo.attrib &  _A_SUBDIR))
            {
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
                    getFiles( pathName.assign(path).append("\\").append(fileinfo.name), exd, files );
            }
            else
            {
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
                    files.push_back(pathName.assign(path).append("\\").append(fileinfo.name));
            }
        }while(_findnext(hFile, &fileinfo)  == 0);
        _findclose(hFile);
    }
}

int *** matrix3D (int x)
{
    int i,j,k;
    int ***p3 ;
    p3 = new int**[x] ;
    for( i = 0 ; i < x ; i ++ )
    {
        p3[i] = new int*[x] ;
    }
    for( i = 0 ; i < x ; i ++ )
    {
        for( j = 0 ; j < x ; j ++ )
        {
            p3[i][j] = new int[x] ;
        }
    }
    for(i = 0 ; i < x ; i ++ )
    {
        for(j = 0 ; j < x ; j ++ )
        {
            for( k = 0 ; k < x ; k ++)
            {
                p3[i][j][k] = 0 ;
            }
        }
    }

    return p3;
}
void getOutput(const char *ss,vtkSmartPointer<vtkPolyData> polydata)
{
	vtkSmartPointer<vtkXMLPolyDataWriter> writer1 =
		vtkSmartPointer<vtkXMLPolyDataWriter>::New();
	writer1->SetFileName(ss);
	writer1->SetInputData(polydata);
	writer1->Write();
}
void VisualiZ()
{

	}

int main()
{
	int i, j, k, temp1, temp2;
    //create vtkpoint
  
	 //create vector

	 //create polydata
 
	 //create cell
	
	 //create imagedata
	 vtkSmartPointer<vtkImageData> imagedata
		 = vtkSmartPointer<vtkImageData>::New();
	 vtkSmartPointer<vtkImageData> imagedata2
		 = vtkSmartPointer<vtkImageData>::New();
	// cout << "get the slicexxx.dat" << endl;
	// string slice_filepath;
	// cin >> slice_filepath;
	 cout << "insert x filepath" << endl;
	 string  x_3d_filepath;// = "C:\\Learning\\2RB100\\v_3d_x";
	 cin >> x_3d_filepath;
	 cout << "insert y filepath" << endl;
	 string  y_3d_filepath;// = "C:\\Learning\\2RB100\\v_3d_y";
	 cin >> y_3d_filepath;
	 cout << "insert z filepath" << endl;
	 string  z_3d_filepath;// = "C:\\Learning\\2RB100\\v_3d_z";
	 cin >> z_3d_filepath;
	// vector<string> slice_files;
	 vector<string> v_x_files;
	 vector<string> v_y_files;
	 vector<string> v_z_files;
	  //获取该路径下的所有dat文件
	//getFiles(slice_filepath, "dat", slice_files);
    getFiles(x_3d_filepath, "dat", v_x_files);
	getFiles(y_3d_filepath, "dat", v_y_files);
	getFiles(z_3d_filepath, "dat", v_z_files);
	//get the number of files
	//int n = slice_files.size();
	int x = v_x_files.size();
	int y = v_y_files.size();
	int z = v_z_files.size();
	//size stores the accounting number of files. 
	vector<float> x_num;
	vector<float> y_num;
	vector<float> z_num;
	//vector<int> n_num;
	

	if ((x==y))
	{
		cout << "start to convert" << endl;	
		imagedata->SetDimensions(x, y, z);
		imagedata->SetSpacing(1.0, 1.0, 1.0);
		imagedata->AllocateScalars(VTK_FLOAT, 3);
	

		int * dims = imagedata->GetDimensions();
		for (i = 0; i < dims[2]; i++)
		{
			for (j = 0; j < dims[1]; j++)
			{
				for (k = 0; k < dims[0]; k++)
				{
					float* voxel = static_cast<float*>(imagedata->GetScalarPointer(j, k, i));
					voxel[0] = 0.0;
					voxel[1] = 0.0;
					voxel[2] = 0.0;
				}
			}
		}
		
		
	/*		if(i%10==0)
		{
			polydata->SetPoints(points);
			polydata->GetPointData()->SetVectors(vectors);
			polydata->SetVerts(soil);

			string numB = int2str(i / 10);
			string s = "test" + numB + ".vtp";
			const char * ss = s.c_str();
			writer->SetFileName(ss);
			writer->SetInputData(polydata);
			writer->Write();
			points->Initialize();
			vectors->Initialize();
			soil->Initialize();
			polydata->Initialize();
			x_num.clear();
			y_num.clear();
			z_num.clear();
		}
	*/			
		for (i = 0; i < x; i++)
		{
			x_num = *InputData_To_Vector_Float(v_x_files[i]);
			y_num = *InputData_To_Vector_Float(v_y_files[i]);
			z_num = *InputData_To_Vector_Float(v_z_files[i]);
		
			
			if ((x_num.size()==y_num.size()))
			{ 
				for ( j = 0; j < x_num.size(); j++)
				{
					temp1 = j % z;
					temp2 = j / z;
					float * voxel = static_cast<float *>(imagedata->GetScalarPointer(temp2, temp1, i));
					voxel[0] = x_num[j];
					voxel[1] = y_num[j];
					voxel[2] = z_num[j];
	
				}
					
			}
		}
	}
	else
	{
		cout << "error, please check the number of files" << endl;
	}
	cout << "end!" << endl;
	//imagedata->GetPointData()->SetActiveVectors("velocity");
	vtkSmartPointer<vtkXMLImageDataWriter> writeImage
		= vtkSmartPointer<vtkXMLImageDataWriter>::New();
	string fileName = "test" + int2str(x) + ".vti";
	writeImage->SetFileName(fileName.c_str());
	writeImage->SetInputData(imagedata);
	writeImage->Write();
	
	
			
				
			
	return 0;
}