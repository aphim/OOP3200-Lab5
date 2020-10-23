#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>


#include "Vector2D.h"



int main()
{
	try
	{
		/************************
		 *	DECLARATIONS
		 ************************/
		std::map<std::string, Vector2D<int>*> filePoints;


		
		/******************************************************************************
		 *	Reading Labels/Points into the Map:
		 *	Attempt to open the data file.  If the data file opens, read a label,
		 *	followed by a point and insert them into the map using the label as the key.
		 *	Repeat until all the data is read and close the file. If the data file did
		 *	not open, tell the user and remind them to check that the file exists. If
		 *	the file opened but the map is empty after the input loop, report that to
		 *	the user and remind them to check that the file contains valid data in
		 *	the correct format. Only continue processing if the file was opened and the
		 *	map is not empty.
		 ******************************************************************************/
		std::ifstream infile;
		std::string fileName;

		std::cout << "Please enter text file to retrieve data from. (eg: MockDataForTesting.txt)"<<std::endl;
		std::cin >> fileName;

		infile.open(fileName.c_str());

		if (infile.is_open())
		{
			float x, y;
			std::string name;

			while (!infile.fail())
			{
				infile >> name;
				infile.ignore(1, ' ');
				infile.ignore(1, '(');
				infile >> x;
				infile.ignore(1, ',');
				infile.ignore(1, ' ');
				infile >> y;
				infile.ignore(1, ')');

				auto* temp_object = new Vector2D<int>(x, y);

				filePoints[name] = temp_object;
			}
			infile.close();
		}
		//Output data points from file for testing purposes
		std::cout << "\n---------------------------------" << std::endl;
		for (const auto& data_points : filePoints)
		{
			std::cout << "Name  : " << data_points.first << std::endl;
			std::cout << "Value: ";
			std::cout << data_points.second->ToString() << std::endl;
			std::cout << "---------------------------------" << std::endl;
		}

		/******************************************************************************
		 *	Determine the Total Distance Between All Points in Order:
		 *	Use an iterator and a loop to traverse each label/point in the map. For
		 *	each label/point, determine the distance from that point to the previous
		 *	point (or next point depending on how you implement this) and add that
		 *	distance to a total.  Note that the Vector2D class includes a static 
		 *	distance function to determine the distance between two Vector2D
		 *	objects, so you should not need to use any complicated math here.  Report
		 *	to the user how many points the map contains and what the total distance is.
		 ******************************************************************************/

				

		/******************************************************************************
		 *	Determine the Distance Between the Start Point and a User Selected Point:
		 *	Prompt the user to enter a label or to enter "quit" to end.  If the user
		 *	entered anything other than "quit", attempt to find the label they entered
		 *	in the map. If it was found, report the distance between the point for the
		 *	label they entered and the start point (i.e. the point labeled "AA").
		 *	Otherwise, tell the user that the label they entered is not in the map.
		 *	Repeat these steps until the user enters "quit".
		 ******************************************************************************/
		
	}
	/******************************************************************************
	 *	Exception Handling:
	 *	Catch any std::exception thrown. Report to the user that a run-time error
	 *	occurred and show what exception was thrown.
	 ******************************************************************************/
	catch(...)  // an exception was thrown
	{
		
	}

	// END-OF-PROGRAM
	
	return 0;
}

