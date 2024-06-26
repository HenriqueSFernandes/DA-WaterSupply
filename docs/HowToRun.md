# Run doxygen

The doxygen documentation is automatically created and deployed to [here](https://da-water-supply.vercel.app/).  
If you wish to manually create the documentation follow these steps.
## 1. Install doxygen

### Ubuntu

`sudo apt install doxygen`

### Arch

`sudo pacman -S doxygen`

Refer to https://www.doxygen.nl/manual/install.html for more information

## 2. Run doxygen

On the top right of CLion, select the `doc_doxygen` build command.  
You might have to select executable (the main program) and the working directory (the `docs` folder).  
This should generate the webpage in `docs/doxygen_documentation/html`.

Another way to run doxygen is to navigate to the `docs` folder and run `doxygen Doxyfile`


## 3. See the documentation

The webpage will be generated in this directory: `docs/doxygen_documentation/html`.  