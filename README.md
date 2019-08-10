# SuiteSparsePythonWindows

This GitHub repository contains a guide on how to install Tim Davis's amazing [SuiteSparse](http://faculty.cse.tamu.edu/davis/suitesparse.html) on a Windows machine, and use it in a C/C++ program with OpenMP interfaced from Python. It builds heavily upon [suitesparse-metis-for-windows](https://github.com/jlblancoc/suitesparse-metis-for-windows) by Jose Luis Blanco and Jerome Esnault.

1. Install [CMake](http://www.cmake.org/donwload) and [Visual Studio 2017 Community](https://visualstudio.microsoft.com/)
2. **Clone** the following repositories:

    * [suitesparse-metis-for-windows](https://github.com/jlblancoc/suitesparse-metis-for-windows) to `C:/suitesparse-metis-for-windows` 
    * [SuiteSparsePythonWindows](https://github.com/JeppeDruedahl/SuiteSparsePythonWindows) to `C:/SuiteSparsePythonWindows` 

3. Run **CMake (cmake-gui)**:
      
    * Set the "Source code" directory to `C:/suitesparse-metis-for-windows/` 
	* Set the "Build" directory to `C:/suitesparse-metis-for-windows/build/`
	* Press "Configure" (accept to create the "build" folder)
	    
        * Generator: Visual Studio 15 2017
        * Optimal platform for generator: x64
        * Press "Finish"

	* Press "Generate"

4. Press **"Open projects"** (opens `C:/suitesparse-metis-for-windows/build/SuiteSparseProject.sln` in Visual Studio)

   * In the top ribbon choose "Debug" and right click on "INSTALL" in the right-hand-side menu and choose "Build" 
   * In the top ribbon choose "Release" and right click on "INSTALL" in the right-hand-side menu and choose "Build" 

5. Run **Edit the system environment variables** 
 
    * Click on "Environment Variables"
    * Choose Path under "System variables" and pres "Edit..."
    * Add `C:/suitesparse-metis-for-windows/build/install/lib64/lapack_blas_windows/`

6. **Copy** `C:/suitesparse-metis-for-windows/build/install/lib64` to `C:/lib64`

7. Run **CMake**:

    * Set the "Source code" directory to `C:/SuiteSparsePythonWindows` 
	* Set the "Build" directory to `C:/SuiteSparsePythonWindows/build`
	* Press "Configure" (accept to create the "build" folder)
	    
        * Generator: Visual Studio 15 2017
        * Optimal platform for generator: x64
        * Press "Finish"

	* Press "Generate"

8. Press **"Open projects"** (opens `C:/SuiteSparsePythonWindows/build/Example.sln` in **Visual Studio**)

   * In the top ribbon choose "Release" and right click on "Example" in the right-hand-side menu and choose "Build"

9. Open `Example.ipynb` and run it.

**Note:** If you update `example.cpp` you now only need to re-run the notebook. Re-building from Visual Studio can, however, be useful for debugging.
