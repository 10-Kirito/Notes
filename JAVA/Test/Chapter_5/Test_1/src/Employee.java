public class Employee {
    private String name;
    private int old;
    private int height;
    private int salary;
    public Employee(String _name, int _old, int _height, int _salary) {name = _name; old = _old; salary = _salary; }
    public int getOld() {return old;}
    public String getName() { return name;}
    public int getHeight() { return height;}
    public void setHeight(int height) { this.height = height; }
    public void setName(String name) { this.name = name; }
    public void setOld(int old) { this.old = old; }
    public int getSalary() { return salary; }
    public void setSalary(int salary) { this.salary = salary; }
}


class Manager extends Employee {
    private String sex;
    private int bonus;
    public Manager(String _name, int _old, int _height, int _salary) {
        super(_name, _old, _height, _salary);
        bonus = 0;
    }

    public String getSex() { return sex; }
    public void setSex(String sex) { this.sex = sex; }
    public int getSalary(){ return super.getSalary() + bonus; }


}