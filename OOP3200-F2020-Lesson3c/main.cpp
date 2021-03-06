/** OOP3200. F2020. Main.cpp
 *
 * In this program, we create a map of data points on a coordinate grid.
 * We then calculate the total distance traveled and allow the user to choose a 
 * point and find the distance to the origin.
 *
* Author: Jacky Yuan, 100520106
*         Ashok Sasitharan, 100745484
* Date: Oct 24, 2020
* Change Log: N/A
*/

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
		std::map<std::string, Vector2D<int>> filePoints;
		std::ifstream infile;
		std::string fileName;
		bool flag = false;



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


		while (flag == false)
		{
			//Prompt for entering file name
			std::cout << "Please enter text file to retrieve data from. (eg: MockDataForTesting.txt, PointData.dat)" << std::endl;
			//receive file name
			std::cin >> fileName;
			bool errorFlag = false;

			//opens the file of the entered file name
			infile.open(fileName.c_str());

			if (infile.is_open())
			{
				//creates variables
				std::string name;
				int x, y;

				//while loop for retrieving points from the document
				while (!infile.fail())
				{
					infile >> name;
					infile.ignore(1, ' ');
					infile.ignore(1, '(');
					//checks for empty space, alphabet characters, or end of page. Raises error flag if it is found.
					char textx = infile.peek();
					if (textx != ' ' && infile.peek() != EOF && isalpha(textx) == false)
					{
						infile >> x;
					}
					else
					{
						errorFlag = true;
					}
					infile.ignore(1, ',');
					infile.ignore(1, ' ');
					//checks for empty space, alphabet characters, or end of page. Raises error flag if it is found.
					char texty = infile.peek();
					if (texty != ' ' && infile.peek() != EOF && isalpha(texty) == false)
					{
						infile >> y;

					}
					else
					{
						errorFlag = true;
					}
					infile.ignore(1, ')');

					//Checks if the error flag is raised
					if (errorFlag == false)
					{
						//Checks if the name is the proper length
						if (name.length() == 2)
						{
							//inserts the vector point into the map
							auto temp_object = Vector2D<int>(x, y);
							filePoints[name] = temp_object;
						}
					}
				}
				infile.close();

				//checks if the map is empty
				if (!filePoints.empty())
				{
					//Output data points from file for testing purposes
					std::cout << "\n---------------------------------" << std::endl;
					for (const auto& data_points : filePoints)
					{
						std::cout << "Name  : " << data_points.first << std::endl;
						std::cout << "Value: ";
						std::cout << data_points.second.ToString() << std::endl;
						std::cout << "---------------------------------" << std::endl;
					}
					flag = true;
				}
				//error case if the map is empty.
				else
				{
					std::system("cls");
					std::cout << "The map is empty. Check that the file contains valid data in the correct format." << std::endl;
					std::cout << "\n-----------------------------------------------------------" << std::endl;
					std::system("pause");
					flag = false;
					std::system("cls");
				}
			}
			//error case for if the file is not found.
			else
			{
				std::system("cls");
				std::cout << fileName << " could not be opened for input. Check that the file exists." << std::endl;
				std::cout << "\n-----------------------------------------------------------" << std::endl;
				std::system("pause");
				flag = false;
				std::system("cls");
			}
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

		float totalDistance = 0.0f;
		int counter = 1;
		
		//for loops through the points in the map
		for (auto& data_points : filePoints)
		{

			//iterator that gets the current key
			auto point1itr = filePoints.find(data_points.first);
			//iterator that gets the key of the point after the current point
			auto point2itr = std::next(filePoints.find(data_points.first), 1);
			//runs if the iterator is not at the end of the map.
			if (point1itr != filePoints.end() && point2itr != filePoints.end())
			{
				counter++;
				//call distance function in variable and send in the Vector2D value for the first and second points
				auto distance = Vector2D<int> ::Distance(point1itr->second, point2itr->second);
				totalDistance += distance;
				std::cout << " Distance between "<< point1itr->first <<" and " << point2itr->first << " is: " << std::setprecision(3) << std::fixed <<distance << "." << std::endl;
			}
			//run when the map has finished looping.
			else
			{
		
				std::cout << "\nThe map contains " << std::to_string(counter) << " points for a total distance of " << totalDistance << "."<< std::endl;
				std::cout << "\n-----------------------------------------------------------" << std::endl;
				
			}
		}
			/******************************************************************************
			 *	Determine the Distance Between the Start Point and a User Selected Point:
			 *	Prompt the user to enter a label or to enter "quit" to end.  If the user
			 *	entered anything other than "quit", attempt to find the label they entered
			 *	in the map. If it was found, report the distance between the point for the
			 *	label they entered and the start point (i.e. the point labeled "AA").
			 *	Otherwise, tell the user that the label they entered is not in the map.
			 *	Repeat these steps until the user enters "quit".
			 ******************************************************************************/
			bool userInputFlag = false;
			float distanceFromStart;
			std::string userInput;
	
			while (userInputFlag == false)
			{
				//output prompt for user input
				std::cout << "\nEnter the label of the point you wish to go to (\"quit\" to end): ";
				std::cin >> userInput;

				//Checks if the user wants to quit
				if (userInput == "quit" || userInput == "Quit" || userInput == "QUIT")
				{
					userInputFlag = true;
				}
				else
				{
					//Searches the map for the inputted point
					auto searchKey = filePoints.find(userInput);
					//Checks if the search result is equal to the end of the map
					if (searchKey != filePoints.end())
					{
						//outputs the distance from the origin to the point
						distanceFromStart = Vector2D<int>::Distance(filePoints["AA"], filePoints[userInput]);
						std::cout << "\nThe distance between AA " << filePoints.at("AA") << " and " << userInput << " " << filePoints.at(userInput) << " is " << distanceFromStart << std::endl;
					}
					//if the user inputted point is not found
					else
					{
						std::cout << "\nThere is no point labeled \"" << userInput << "\" in the map." << std::endl;
					}
				}
			}
		
		/******************************************************************************
		 *	Exception Handling:
		 *	Catch any std::exception thrown. Report to the user that a run-time error
		 *	occurred and show what exception was thrown.
		 ******************************************************************************/
	}
		catch (std::exception e)  // an exception was thrown
		{
			std::cout << "Runtime error: " << e.what();
		}


		// END-OF-PROGRAM

	
	
	return 0;
}