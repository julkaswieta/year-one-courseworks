/** 
 * @author Bjarne Stroustrup
 */
public class Rectangle {
    
    private double length;
    private double width;
    private int xCoordinate;
    private int yCoordinate;

    /**
     * Query for the length of the rectangle.
     * @return the length
     */
    public double getLength ( ) {
        return this.length;
    }

    /**
     * Sets the length of the rectangle.
     * @param length the length
     */
    public void setLength ( double length ) {
        this.length = length;
    }

    /**
     * Query for the width of the rectangle.
     * @return the width
     */
    public double getWidth ( ) {
        return this.width;
    }

    /**
     * Sets the width of the rectangle.
     * @param width the width
     */
    public void setWidth ( double width ) {
        this.width = width;
    }

    /**
     * Query for the area of the rectangle.
     * @return the area (length * width)
     */
    public double getArea ( ) {
        return this.length * this.width;
    }

     /**
     * Query for the x coordinate of the rectangle.
     * @return the x coordinate
     */
    public int getX ( ) {
        return this.xCoordinate;
    }

    /**
     * Query for the y coordinate of the rectangle.
     * @return the y coordinate
     */
    public int getY ( ) {
        return this.yCoordinate;
    }

    /**
     * Moves the rectangle to a new position.
     * @param x the new x coordinate
     * @param y the new y coordinate
     */
    public void moveTo ( int x, int y ) {
        this.xCoordinate = x;
        this.yCoordinate = y;
    }

    /**
     * @return a string representation of the Rectangle
     */
    public String toString ( ) {
        return "width: " + this.width + ", " +
                "length:" + this.length + ", " +
                "x coordinate: " + this.xCoordinate + ", " +
                "y coordinate: " + this.yCoordinate;
    }

}

