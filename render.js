//defining some globals (a bit redundant)
var width = 320,
    height = 320,
    objects = [],
    lights = [],
    c = document.getElementById('c'),
    ctx = c.getContext('2d');

//set canvas size
c.width = width;
c.height = height;

//Debug function for console printing
function log(msg) {
    setTimeout(function() {
        throw new Error(msg);
    }, 0);
}

//Vector class
var VectorClass = function(coordX,coordY,coordZ)
{
    //Ray starting point
    this.x = coordX;
    this.y = coordY;
    this.z = coordZ;
};

//Adding some functions
VectorClass.prototype = {

    //Object properties
    x: 0,
    y: 0,
    z: 0,
    
    //Add two vectors
    add: function()
    {
        return new VectorClass(this.x+arguments[0].x, this.y+arguments[0].y ,this.z+arguments[0].z);
    },

    //Substract two vectors
    substract: function()
    {
        return new VectorClass(this.x-arguments[0].x, this.y-arguments[0].y ,this.z-arguments[0].z);
    },

    //Scalar multiplication
    multiply: function()
    {
        return new VectorClass(this.x*arguments[0], this.y*arguments[0], this.z*arguments[0]);
    },

    //Dot product
    dot: function()
    {
        return this.x*arguments[0].x + this.y*arguments[0].y + this.z*arguments[0].z;
    }
};


//(light) Ray class
var RayClass = function(positionVector,directionVector)
{
    //Light ray origin and direction
    this.position = positionVector;
    this.direction = directionVector;
}

//Sphere class
var SphereClass = function(positionVector,radius)
{
    //Sphere position
    this.position = positionVector;
    //Radius
    this.radius = radius;
};

SphereClass.prototype = {

    position: 0,
    radius: 0,

    //Ray-sphere intersection can be solved with
    //quadratic equation (Ax^2+Bx+C = 0)
    intersect: function()
    {
        //Assume sphere in origin and move ray position in realtion
        //to simplify the equation
        var distance = this.position.substract(arguments[0].position);

        //Actual ray
        var B = arguments[0].direction.dot(distance);

        //Discriminant
        var D = B*B - distance.dot(distance) + this.radius * this.radius; 

        //Only imaginary roots, does not intersect
        if(D < 0)
            return NaN;

        //Get solutions, minus before B not needed because its the same
        //just opposite direction.
        var t0 = B - Math.sqrt(D);
        var t1 = B + Math.sqrt(D);
        
        //0.1 to avoid reflection artifacts due limited precision
        if((t0 > 0.1) && (t0 < t1))
            return t0;
        else if((t1 > 0.1) && (t1 < t0))
            return t1;
        //No intersection within precision
        else
            return NaN;
    }
};

//Fill the canvas with background pattern
var clear = function()
{
    ctx.fillStyle = "White";
    ctx.beginPath();
    ctx.rect(0,0,width,height);
    ctx.closePath();
    ctx.fill();
};

//Main function
function render()
{
    //Clear the old frame
    clear();
    
    //Our 'camera' position
    var camPos = new VectorClass(0,0,-150),
    //In which direction the camera points
        camDir = new VectorClass(0,0,1),
    //Ray object
        ray = new RayClass(camPos,camDir), 
    //Color of a pixel
        color = 0;

    //Camera position is in the middle of the screen
    //starting from topleft
    ray.position.y -= height/2;
    //Each row starts from the left
    ray.position.x -= width/2;

    //Shoot rays from each pixel
    for(var y = 0; y < height; y++)
    {

        for(var x = 0; x < width; x++)
        {
            color = 0; 
            
            //Each object has its own intersect function
            var intersection = objects[0].intersect(ray);
            
            //There are more objects get the closest
            if(objects.length > 1)
            {
                //log("Testing second object.");
                //Test for each object if ray hits it
                for(var obj = 1; obj < objects.length; obj++)
                {
                    var newInter = objects[obj].intersect(ray); 
                    if(!isNaN(newInter) && newInter < intersection)
                    {
                        log("Second object is closer");
                        intersection = newInter;
                    }
                }
            }

            // Intersection exists
            if(!isNaN(intersection))
            {
                //log("INTERSECT: "+intersection + " @ "+x+","+y);
                for(var l = 0; l < lights.length; l++)
                {
                    //If dot product of intersecting vector
                    //and light vector is positive the 
                    //point is visible to the light source
                    var lengthVector = ray.direction.multiply(intersection);
                    var intersectPoint = ray.position.add(lengthVector);
                     
                    if(intersectPoint.dot(lights[l]) > 0)
                    {
                        color = 255;
                    }
                }
            }
             
            // Paint the pixel
            ctx.fillStyle = 'rgba('+color+','+color+',0,1)';
            ctx.beginPath();
            ctx.rect(x,y,1,1);
            ctx.closePath();
            ctx.fill();
             
            //Next pixel
            ray.position.x += 1;
        }

        //Back to the leftmost pixel
        ray.position.x -= width;
        
        //Next row
        ray.position.y += 1;
    }
};

function init()
{
    //Insert light in to the scene
    lights[0] = new VectorClass(30,-70,-110);

    //Insert sphere in the scene
    objects[0] = new SphereClass(new VectorClass(0,0,0),40);
    objects[1] = new SphereClass(new VectorClass(80,80,0),20);
}


log("Hello!");
init();
render();
//clear();
//init();
//    var camPos = new VectorClass(0,1,-50),
//    //In which direction the camera points
//        camDir = new VectorClass(0,0,1),
//    //Ray object
//        ray = new RayClass(camPos,camDir); 
//ctx.fillStyle = "Black";
//var distance = objects[0].position.substract(ray.position);
//var B = ray.direction.dot(distance);
//var D = B*B - distance.dot(distance) + objects[0].radius * objects[0].radius; 
//var inter = objects[0].intersect(ray);
//
//var lengthVector = ray.direction.multiply(inter);
//var intersectPoint = ray.position.add(lengthVector);
//                         
//var iDir = intersectPoint.dot(lights[0])
//
//
//ctx.fillText("INTERSECT "+ (B - Math.sqrt(D)),10,10);
//ctx.fillText("SPHERE "+inter,10,20);
//ctx.fillText("LENGTH "+lengthVector.x+","+lengthVector.y+","+lengthVector.z,10,30);
//ctx.fillText("POINT "+intersectPoint.x+","+intersectPoint.y+","+intersectPoint.z,10,40);
//ctx.fillText("DIR "+iDir,10,50);



