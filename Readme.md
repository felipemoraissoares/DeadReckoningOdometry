# Robotic Odometry Model Using Dead Reckonig 

This project presents a technique for estimating the current position of a robot called odometry. Odometry will be performed using Dead Reckoning algorithms. The concept of odometry and Dead Reckoning will be explained, using a practical experiment for the movement of the Robot called Potter. Potter is a robot of automation and robotics Group (Garra) from Federal University of Santa Maria (UFSM). The robot will be performing the path of a square. To carry out the navigation of the robotic base, not only the robot Potter, but as in all others of this model, in an environment unknown, some mechanisms for its detection are necessary, such as its positioning and location must be provided to its base. The purpose of this project, is to verify the functioning of the odometry, making the robot move more precisely during the stipulated path. This project was carried out on the premises of the Federal University of Santa Maria (UFSM) under the guidance of Professor Daniel Fernando Tello Gamarra.

### Odometry

```
The purpose of odometry is to calculate the current position of the robot x’, y’, theta’, through its origin position. Odometry geometry. Over a small time period, the robot’s motion can be approximated by an arc. The odometry problem is to solve for (x0, y0, µ0) given (x, y, µ) and dbaseline. In the figure, the robot is moving counter-clockwise.
```

<img align=center
	src='https://ik.imagekit.io/eogtlka8vuq/Medias_Github/1_-CEWuCjw2.PNG' style="zoom:50%;" >

### Dead-reckoning Sensors

```
Dead reckoning is the process of calculating current position by using previously determined reference position and advancing that position based upon known or estimated speeds over elapsed time and course. In the case of Potter, has two independent motors, the encoders, and a rear wheel that has free movement. As the wheel moves, the encoder has its value increased. Each pulse received by the encoder represents a fraction of the wheel's turn. The distance the wheel travels on the ground with each encoder pulse can be calculated by dividing the wheel circumference by the number of pulses the encoder provides in an entire wheel revolution 
```

<img align=center
	src='https://ik.imagekit.io/eogtlka8vuq/Medias_Github/3_-QJSgaHcqX.PNG' style="zoom:50%;" >



### Components

* Arduino Mega 

  <img align=center
  	src='https://ik.imagekit.io/eogtlka8vuq/Medias_Github/3_-QJSgaHcqX.PNG' style="zoom:50%;" >

* Motors EMG49

  <img align=center
  	src='https://ik.imagekit.io/eogtlka8vuq/Medias_Github/7__dmGZYbu4.PNG' style="zoom:50%;" >

* Driver M49

  <img align=center
  	src='https://ik.imagekit.io/eogtlka8vuq/Medias_Github/8_SKAZuXJVi.PNG' style="zoom:0%;" >

* Potter Robot

  <img align=center
  	src='https://ik.imagekit.io/eogtlka8vuq/Medias_Github/2_2TktzuGW8.PNG' style="zoom:0%;" >

  


### Aplication 

* Arduino : All parts of Potter movement, calculations and Dead Reckoning Odometry was made in arduino and developed em C language. 
* Matlab : Using for estimate teorical x real expirience, and plot ther graphics



### Results 

* Theoretical measure

  <img align=center
  	src='https://ik.imagekit.io/eogtlka8vuq/Medias_Github/4_aa8A9i8aNn.PNG' style="zoom:50%;" >

* Real measure

  <img align=center
  	src='https://ik.imagekit.io/eogtlka8vuq/Medias_Github/5_bAXmvujV11.PNG' style="zoom:50%;" >

* Theoretical x Real 

  <img align=center
  	src='https://ik.imagekit.io/eogtlka8vuq/Medias_Github/6_aJFsJR6hQu.PNG' style="zoom:50%;" >

  
