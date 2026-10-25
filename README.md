# OACT_solar_cycles_data_analysis
OACT solar cycles data analysis

This program creates nice solar cycles plots from OACT USSPS files archive.\
The master file is [OACT_Sun.ipynb](OACT_Sun.ipynb), it has been used to create the plots in png format.\
The C codes were used to mine the physical information from the USSPS files and to store them in some txt files that are read by the master file. \
All the USSPS files are stored in the OACT server and it has been possible to analyze them due to the explanation given in the website: https://solar.oact.inaf.it/Latest_USSPS_file.php

Hint: start reading [OACT_Sun.ipynb](OACT_Sun.ipynb)

Sources:
* https://solar.oact.inaf.it/USSPS_archive.php
* https://www.sidc.be/SILSO/infosndtot ---> [SN_d_tot_V2.0.txt](SN_d_tot_V2.0.txt)

Data editing codes:
* [lat.c](lat.c)
* [sunspotsarea.c](sunspotsarea.c)
* [spotcount.c](spotcount)
* [SILSO.c](SILSO.c)
* [OACT_Sun.ipynb](OACT_Sun.ipynb)

Plots maker:
* [OACT_Sun.ipynb](OACT_Sun.ipynb)

Final plots:
* [butterfly_diagram.png](butterfly_diagram.png)
* [sunspot_area_evolution.png](sunspot_area_evolution.png)
* [sunspots_OACT.png](sunspots_OACT.png)
* [sunspots_SILSO.png](sunspots_SILSO.png)
