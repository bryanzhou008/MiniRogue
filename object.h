//
//  object.h
//  Project3
//
//  Created by Bryan Zhou on 5/15/20.
//  Copyright © 2020 Bryan Zhou. All rights reserved.
//

#ifndef object_h
#define object_h
#include <string>



class object
{
public:
    // Constructor/destructor
    object(int row, int col, char icon, std::string name)
    :m_row(row), m_col(col), m_icon(icon), m_name(name)
    {
    }
    virtual ~object(){}
    
    // Accessors
    int getRow() const {return m_row;}
    int getCol() const {return m_col;}
    
    
    char getIcon() const {return m_icon;}
    std::string getName() const {return m_name;}
    
    
    // Mutators
    
    void setRow(int r) {m_row =r;}
    void setCol(int c) {m_col =c;}
    
    
    void moveToInventory()
    {
        m_row = -1;
        m_col = -1;
    }

    
private:
    int m_row;
    int m_col;
    
    char m_icon;
    std::string m_name;
    
   
    
    
};








class weapon: public object
{
public:
    // Constructor/destructor
    weapon(int r, int c, std::string name, std::string action, int bonus, int damage)
    :object(r,c,')',name), m_action(action), m_bonus(bonus), m_damage(damage)
    {
    }
    virtual ~weapon(){}

    
    
    
    
    // Accessors
    std::string getAction() const {return m_action;}
    int getBonus() const {return m_bonus;}
    int getDamage() const {return m_damage;}
    
    char icon() const {return ')';}
   

    // Mutators


private:
    std::string m_action;
    int m_bonus;
    int m_damage;
    
    
    
    

};



class scroll: public object
{
public:
    // Constructor/destructor
    scroll(int r, int c,std::string name, int myId, std::string actionString)
    :object(r, c, '?', name), m_id(myId), m_actionString(actionString)
    {
        
    }
    virtual ~scroll(){}

    // Accessors
    char icon() const {return '?';}
    int getMyId() const {return m_id;}
    std::string getActionString() const {return m_actionString;}
    
    
    
    // Mutators
    

private:
    int m_id;
    std::string m_actionString;
};






class mace: public weapon
{
public:
    // Constructor/destructor
    mace(int r, int c)
    :weapon(r, c, "mace", "swings mace at", 0, 2)
    {
        
    }
    
    mace()
    :weapon(-1,-1,"mace", "swings mace at", 0, 2)           //constructor for once initialized in the inventory or monster's hands
    {
        
    }
    virtual ~mace(){}
    
    // Accessors
    
    
    // Mutators
    
    
    
private:
    
};

class S_sword: public weapon
{
public:
    // Constructor/destructor
    S_sword(int r, int c)
    :weapon(r, c, "short sword", "slashes short sword at", 0, 2)
    {
        
    }
    S_sword()
    :weapon(-1, -1, "short sword", "slashes short sword at", 0, 2)
    {
        
    }
    virtual ~S_sword(){}
    
    // Accessors
    
    
    // Mutators
    
    
    
private:
    
};

class L_sword: public weapon
{
public:
    // Constructor/destructor
    L_sword(int r, int c)
    :weapon(r, c, "long sword", "swings long sword at", 2, 4)
    {
        
    }
    
    L_sword()
    :weapon(-1, -1, "long sword", "swings long sword at", 2, 4)
    {
        
    }
    virtual ~L_sword(){}
    
    // Accessors
    
    
    // Mutators
    
    
    
private:
};

class axe: public weapon
{
public:
    // Constructor/destructor
    axe(int r, int c)
    :weapon(r, c, "magic axe", "chops magic axe at", 5, 5)
    {
        
    }
    axe()
    :weapon(-1, -1, "magic axe", "chops magic axe at", 5, 5)
    {
        
    }
    virtual ~axe(){}
    
    // Accessors
    
    
    // Mutators
    
    
    
private:
};

class fang: public weapon
{
public:
    // Constructor/destructor
    fang(int r, int c)
    :weapon(r, c, "magic fangs of sleep", "strikes magic fangs at", 3, 2)
    {
        
    }
    fang()
    :weapon(-1, -1, "magic fangs of sleep", "strikes magic fangs at", 3, 2)
    {
        
    }
    virtual ~fang(){}
    
    // Accessors
    
    
    // Mutators
    
    
    
private:
};




class Tele: public scroll
{
    public:
        // Constructor/destructor
        Tele(int r, int c)
        :scroll(r,c,"scroll of teleportation",1,"You feel your body wrenched in space and time.")
        {
            
        }
    virtual ~Tele(){}

        // Accessors
        
        
        
        
        // Mutators
        

    private:
   

};


class Iarm: public scroll
{
    public:
        // Constructor/destructor
        Iarm(int r, int c)
        :scroll(r,c,"scroll of enhance armor",2,"Your armor glows blue.")
        {
            
        }
    virtual ~Iarm(){}

        // Accessors
        
        
        
        
        // Mutators
        

    private:
   
};


class Istr: public scroll
{
    public:
        // Constructor/destructor
        Istr(int r, int c)
        :scroll(r,c,"scroll of enhance armor",3,"Your muscles bulge.")
        {
            
        }
    virtual ~Istr(){}

        // Accessors
        
        
        
        
        // Mutators
        

    private:
    
};


class Ihel: public scroll
{
    public:
        // Constructor/destructor
        Ihel(int r, int c)
        :scroll(r,c,"scroll of enhance health",4,"You feel your heart beating stronger.")
        {
            
        }
    virtual ~Ihel(){}

        // Accessors
       
        
        
        
        // Mutators
        

    private:
   
};

class Idex: public scroll
{
    public:
        // Constructor/destructor
        Idex(int r, int c)
        :scroll(r,c,"scroll of enhance dexterity",5,"You feel like less of a klutz.")
        {
            
        }
    virtual ~Idex(){}

        // Accessors
    
        
        
        
        // Mutators
        

    private:
    
};





#endif /* object_h */
