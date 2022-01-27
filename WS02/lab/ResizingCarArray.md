# record function resizing the Car arry

- if the [number of cars](#file-scoped-variables) is equal to the size of [the carr array](#file-scoped-variables) it means that the  [Car Array](#file-scoped-variables) is full, we have to enlarge it to make room for more entry<br />
![step one](../images/resize1.png)
    - in a temporary local car pointer dynamically allocate an array of car to the size of ```the car array + the allocation size```.<br />
    ![step two](../images/resize2.png)
    - copy all the cars from the old array to the new array (but do not dellocate the indivudual old cars since their make an model in momory are now pointed by the cars in the new array)<br />
    ![step thre](../images/resize3.png)
    - delete the old car array by deleting ```The Car Pointer```<br />
    ![step four](../images/resize4.png)
    ![step five](../images/resize5.png)
    - set ```The Car Pointer``` to the value of the temporary local car pointer
    - update the carr array size to the new size<br />
    ![step six](../images/resize6.png)

- copy the ```car argument``` after the last occupied element of the car array pointed by ```The Car Pointer``` and add one to the ```number of cars```.<br />
![step sever](../images/resize7.png)

Other versions   

[PDF](ResizingCarArray.pdf)<br/> [Power point](ResizingCarArray.pptx)







