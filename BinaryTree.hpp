#pragma once
#include <typeinfo>
#include <iostream>
#include <string>
#include <memory>
using namespace std;

namespace ariel
{

template<typename T> class BinaryTree
{
    struct Node
    {
        // Node* left_child;
        // Node* right_child;
        // Node* parent;
        shared_ptr<Node> left_child;
        shared_ptr<Node> right_child;
        shared_ptr<Node> parent;
        T data;
        Node(T d,shared_ptr<Node>const & p=nullptr):data(d)
        {
            right_child=shared_ptr<Node>(nullptr);
            left_child=shared_ptr<Node>(nullptr);
            parent=p;
        }
        ~Node()
        {
            
        }
        // int size()
        // {
        //     return 1;
        // }
    };

    class PreOrder
    {
        
        public:
        // Node* current_node;//the current node that the Iter is on 
        shared_ptr<Node> current_node;
        shared_ptr<Node> last_node;
        PreOrder(shared_ptr<Node> n=nullptr)
        {
            current_node=n;
            shared_ptr<Node> temp=n;// Node* temp=root;
            while(temp->right_child!=nullptr)
            {
                temp=temp->right_child;
            }
            last_node=temp;
        }
        PreOrder(shared_ptr<Node> n,int d)
        {
            current_node=n;
        }
        T* operator->()const //return the adress of the current node data
        {
            return &(current_node->data);
        }
        
        T& operator*()//return the data of the current node
        {
            return current_node->data;
        }
        PreOrder& operator++()
        {
            if(current_node==last_node)
            {
               current_node= nullptr; 
            }
            else{
            if(current_node->left_child!=nullptr)
            {
                current_node=current_node->left_child;
            }
            else if(current_node->right_child!=nullptr)
            {
                current_node=current_node->left_child;
            }
            else
            {
                while(current_node->right_child==nullptr)
                {
                    if(current_node->parent->right_child==current_node)
                    {
                        current_node=current_node->parent;
                    }
                    current_node=current_node->parent;
                }
                current_node=current_node->right_child;
            }
            }
            return *this;
        } 
        PreOrder operator++(int n)
        {
            PreOrder p{current_node,1};
            if(current_node==last_node)
            {
               current_node= nullptr; 
            }
            else
            {
            if(current_node->left_child!=nullptr)
            {
                current_node=current_node->left_child;
            }
            else if(current_node->right_child!=nullptr)
            {
                current_node=current_node->left_child;
            }
            else
            {
                while(current_node->right_child==nullptr)
                {
                    if(current_node->parent->right_child==current_node)
                    {
                        current_node=current_node->parent;
                    }
                    current_node=current_node->parent;
                }
                current_node=current_node->right_child;
            }
            }
            return p;
        } 
        bool operator==(const   PreOrder& other) const
        {
            if(current_node==other.current_node)//if the adressers of the two current nodes are the same -> return true
            {
                return true;
            }
            return false;
        }
        bool operator!=(const  PreOrder& other) const
        {
            if(current_node!=other.current_node)
            {
                return true;
            }
            return false;
        }
    };



    class PostOrder
    {
        public:
        // Node* current_node;//the current node that the Iter is on 
        shared_ptr<Node> current_node;
        shared_ptr<Node> last_node;
        PostOrder(shared_ptr<Node> n=nullptr)
        {
            last_node=n;
            current_node=n;
            while(current_node->left_child!=nullptr)
            {
                current_node=current_node->left_child;
            }
        }
        PostOrder(shared_ptr<Node> n,int d)//just a constructor for the endPostOrder function iter
        {
            current_node=n;
        }
        T* operator->()const //return the adress of the current node data
        {
            return &(current_node->data);
        }
        
        T& operator*()//return the data of the current node
        {
            return current_node->data;
        }
        PostOrder& operator++()
        {
            if(current_node==last_node)
            {
               current_node= nullptr; 
            }
            else{
            int from_where=0;//0=parent ,1=left child, 2=right child
            if(current_node->left_child!=nullptr && from_where==0)
            {
                while(current_node->left_child!=nullptr)
                {
                    current_node=current_node->left_child;
                }
                from_where=0;
            }
            // if(current_node->right_child!=nullptr)
            // {
            //    while(current_node->left_child!=nullptr)
            //     {
            //         current_node=current_node->left_child;
            //     }
            //     from_where=0;
            // }
            else if(current_node->parent->left_child==current_node)
            {
                current_node=current_node->parent->right_child;
                while(current_node->left_child!=nullptr)
                {
                    current_node=current_node->left_child;
                }
                from_where=0;
            }
            else if(current_node->parent->right_child==current_node)
            {
                current_node=current_node->parent;
                from_where=2;
            }
            }
            return *this;
        } 
        PostOrder operator++(int n)
        {
            PostOrder p{current_node,1};
            if(current_node==last_node)
            {
               current_node= nullptr; 
            }
            else{
            int from_where=0;//0=parent ,1=left child, 2=right child
            if(current_node->left_child!=nullptr && from_where==0)
            {
                while(current_node->left_child!=nullptr)
                {
                    current_node=current_node->left_child;
                }
                from_where=0;
            }
            else if(current_node->parent->left_child==current_node)
            {
                current_node=current_node->parent->right_child;
                while(current_node->left_child!=nullptr)
                {
                    current_node=current_node->left_child;
                }
                from_where=0;
            }
            else if(current_node->parent->right_child==current_node)
            {
                current_node=current_node->parent;
                from_where=2;
            }
            }
            return p;
        } 
        bool operator==(const   PostOrder& other) const
        {
            if(current_node==other.current_node)//if the adressers of the two current nodes are the same -> return true
            {
                return true;
            }
            return false;
        }
        bool operator!=(const  PostOrder& other) const
        {
            if(current_node!=other.current_node)
            {
                return true;
            }
            return false;
        }
    };

    class InOrder
    {
        public:
        // Node* current_node;//the current node that the Iter is on 
        shared_ptr<Node> current_node;
        shared_ptr<Node> last_node;
        InOrder(shared_ptr<Node> n=nullptr)
        {
           current_node=n;
           while(current_node->left_child!=nullptr)
           {
               current_node=current_node->left_child;
           }
           shared_ptr<Node> temp=n;//Node* temp=root;
            while(temp->right_child!=nullptr)
            {
                temp=temp->right_child;
            }
            last_node=temp;
        }
        InOrder(shared_ptr<Node> n,int d)
        {
            current_node=n;
        }
        T* operator->()const //return the adress of the current node data
        {
            return &(current_node->data);
        }
        
        T& operator*()//return the data of the current node
        {
            return current_node->data;
        }
        InOrder& operator++()
        {
            if(current_node==last_node)
            {
               current_node= nullptr; 
            }
            else{
            int from_where=0;//0=parent ,1=left child, 2=right child
            if(current_node->left_child!=nullptr && from_where==0)
            {
                while(current_node->left_child!=nullptr)
                {
                    current_node=current_node->left_child;
                }
                from_where=0;
            }
            if(current_node->right_child!=nullptr)
            {
               while(current_node->left_child!=nullptr)
                {
                    current_node=current_node->left_child;
                }
                from_where=0;
            }
            else if(current_node->parent->left_child==current_node)
            {
                current_node=current_node->parent;
                from_where=1;
            }
            else if(current_node->parent->right_child==current_node)
            {
                current_node=current_node->parent->parent;
                while(current_node->right_child==nullptr)
                {
                    current_node=current_node->parent;
                }
                from_where=2;
            }
            }
            return *this;
        } 
         InOrder operator++(int n)
        {
            InOrder p{current_node,1};
            int from_where=0;//0=parent ,1=left child, 2=right child
            if(current_node==last_node)
            {
               current_node= nullptr; 
            }
            else
            {
            if(current_node->left_child!=nullptr && from_where==0)
            {
                while(current_node->left_child!=nullptr)
                {
                    current_node=current_node->left_child;
                }
                from_where=0;
            }
            if(current_node->right_child!=nullptr)
            {
               while(current_node->left_child!=nullptr)
                {
                    current_node=current_node->left_child;
                }
                from_where=0;
            }
            else if(current_node->parent->left_child==current_node)
            {
                current_node=current_node->parent;
                from_where=1;
            }
            else if(current_node->parent->right_child==current_node)
            {
                current_node=current_node->parent->parent;
                while(current_node->right_child==nullptr)
                {
                    current_node=current_node->parent;
                }
                from_where=2;
            }
            }
            return p;
        } 
        bool operator==(const   InOrder& other) const
        {
            if(current_node==other.current_node)//if the adressers of the two current nodes are the same -> return true
            {
                return true;
            }
            return false;
        }
        bool operator!=(const  InOrder& other) const
        {
            if(current_node!=other.current_node)
            {
                return true;
            }
            return false;
        }
    };
    
private:
    // Node* root;
    shared_ptr<Node> root;
public:
    BinaryTree(): root(nullptr)
    {
        
    }
    BinaryTree(BinaryTree<T> const & b): root(nullptr)
    {
        deep_copy(root,b.root);
    }
    void deep_copy(shared_ptr<Node>& root,shared_ptr<Node>const & other_root)
    {
        if(other_root==nullptr)
        {
            return;
        }
        if(other_root->parent==nullptr)
        {
            root = make_shared<Node>(other_root->data);
        }
        if(other_root->right_child!=nullptr)
        {
            root->right_child=make_shared<Node>(other_root->right_child->data,root);
            deep_copy(root->right_child,other_root->right_child);
        }
        if(other_root->left_child!=nullptr)
        {
            root->left_child=make_shared<Node>(other_root->left_child->data,root);
            deep_copy(root->left_child,other_root->left_child);
        }
    }
    ~BinaryTree()
    {
        
    }
    BinaryTree<T>& operator=(const BinaryTree<T>& b)
    {
        deep_copy(root,b.root);
        return *this;
    }
    BinaryTree& operator=(BinaryTree&& b)noexcept
    {
        root=b.root;
        b.root=nullptr;
        return *this;
    }
    BinaryTree& add_root(T i)
    {
        // Node r{i};
        root=make_shared<Node>(i);
        return *this;
    }
    BinaryTree& add_left(T in_tree, T i)
    {
        PreOrder it{root};
        while(!(*it == in_tree) && it!=end_preorder()){ ++it;}
        if(*it== in_tree)
        {
            shared_ptr<Node> l=make_shared<Node>(i,it.current_node);// Node n{i,it.current_node};
            it.current_node->left_child=l;
        }
        else{
            throw logic_error("there isnt a node with this value in the tree");
        }
        
        return *this;
    }
    BinaryTree& add_right(T in_tree, T i)
    {
        PreOrder it{root};
        while(!(*it == in_tree) && it!=end_preorder()){ ++it;}
        if(*it== in_tree)
        {
            shared_ptr<Node> r=make_shared<Node>(i,it.current_node);//Node n{i,it.current_node};
            it.current_node->right_child=r;
        }
        else{
            throw logic_error("there isnt a node with this value in the tree");
        }
        return *this;
    }
    PreOrder begin_preorder()
    {
        return PreOrder{root};
    }
    PreOrder end_preorder()
    {
        // shared_ptr<Node> temp=root;// Node* temp=root;
        // while(temp->right_child!=nullptr)
        // {
        //     temp=temp->right_child;
        // }
        // return PreOrder{temp};
        return PreOrder{nullptr,1};
    }
    PostOrder begin_postorder()
    {
        return PostOrder{root};
    }


    PostOrder end_postorder()
    {
        return PostOrder{nullptr,1};//PostOrder{root,1};
    }
    InOrder begin_inorder()
    {
        return InOrder{root};
    }
    InOrder end_inorder()
    {
        // shared_ptr<Node> temp=root;//Node* temp=root;
        // while(temp->right_child!=nullptr)
        // {
        //     temp=temp->right_child;
        // }
        // return InOrder{temp};
        return InOrder{nullptr,1};
    }
    InOrder begin()
    {
        return InOrder{root};
    }
    InOrder end()
    {
        return end_inorder();
    }
    friend std::ostream& operator<<(std::ostream& output,const BinaryTree& t )
    {
        for (auto it=t.begin_inorder(); it!=t.end_inorder(); ++it) 
        {
            cout << (*it) << " " ;
        }  
        return output;
    }    
};

};