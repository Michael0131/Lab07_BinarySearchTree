/***********************************************************************
 * Header:
 *    BST
 * Summary:
 *    Our custom implementation of a BST for set and for map
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *    This will contain the class definition of:
 *        BST                 : A class that represents a binary search tree
 *        BST::iterator       : An iterator through BST
 * Author
 *    Michael, James, Brayden
 ************************************************************************/

#pragma once

#ifdef DEBUG
#define debug(x) x
#else // !DEBUG
#define debug(x)
#endif // !DEBUG

#include <cassert>
#include <utility>
#include <memory>     // for std::allocator
#include <functional> // for std::less
#include <utility>    // for std::pair
#include <initializer_list>

class TestBST; // forward declaration for unit tests
class TestMap;
class TestSet;

namespace custom
{

    template <class TT>
    class set;
    template <class KK, class VV>
    class map;

    /*****************************************************************
     * BINARY SEARCH TREE
     * Create a Binary Search Tree
     *****************************************************************/
    template <typename T>
    class BST
    {
        friend class ::TestBST; // give unit tests access to the privates
        friend class ::TestMap;
        friend class ::TestSet;

        template <class KK, class VV>
        friend class map;

        template <class TT>
        friend class set;

        template <class KK, class VV>
        friend void swap(map<KK, VV>& lhs, map<KK, VV>& rhs);
    public:
        //
        // Construct
        //

        BST();
        BST(const BST& rhs);
        BST(BST&& rhs);
        BST(const std::initializer_list<T>& il);
        ~BST();

        //
        // Assign
        //

        BST& operator = (const BST& rhs);
        BST& operator = (BST&& rhs);
        BST& operator = (const std::initializer_list<T>& il);
        void swap(BST& rhs);

        //
        // Iterator
        //

        class iterator;
        iterator   begin() const noexcept;
        iterator   end()   const noexcept { return iterator(nullptr); }

        //
        // Access
        //

        iterator find(const T& t);

        //
        // Insert
        //

        std::pair<iterator, bool> insert(const T& t, bool keepUnique = false);
        std::pair<iterator, bool> insert(T&& t, bool keepUnique = false);

        //
        // Remove
        //

        iterator erase(iterator& it);
        void   clear() noexcept;

        //
        // Status
        //

        bool   empty() const noexcept { return numElements == 0; }
        size_t size()  const noexcept { return numElements; }


    private:

        class BNode;
        BNode* root;              // root node of the binary search tree
        size_t numElements;        // number of elements currently in the tree

        void deleteBinaryTree(BNode*& p) noexcept;
    };


    /*****************************************************************
     * BINARY NODE
     * A single node in a binary tree. Note that the node does not know
     * anything about the properties of the tree so no validation can be done.
     *****************************************************************/
    template <typename T>
    class BST <T> ::BNode
    {
    public:
        //
        // Construct
        //
        BNode()
        {
            // ---------- (Michael Code to Complete) ----------
            pLeft = pRight = pParent = nullptr;
            isRed = false;
        }
        BNode(const T& t) : data(t)
        {
            // ---------- (Michael Code to Complete) ----------
            pLeft = pRight = pParent = nullptr;
            isRed = false;
        }
        BNode(T&& t) : data(std::move(t))
        {
            // ---------- (Michael Code to Complete) ----------
            pLeft = pRight = pParent = nullptr;
            isRed = false;
        }

        //
        // Insert
        //
        void addLeft(BNode* pNode);
        void addRight(BNode* pNode);
        void addLeft(const T& t);
        void addRight(const T& t);
        void addLeft(T&& t);
        void addRight(T&& t);

        //
        // Status
        //
        bool isRightChild(BNode* pNode) const { return pNode && pNode->pParent == this && pRight == pNode; }
        bool isLeftChild(BNode* pNode) const { return pNode && pNode->pParent == this && pLeft == pNode; }

        //
        // Data
        //
        T data;                  // Actual data stored in the BNode
        BNode* pLeft;            // Left child - smaller
        BNode* pRight;           // Right child - larger
        BNode* pParent;          // Parent
        bool isRed;              // Red-black balancing stuff
    };

    /**********************************************************
     * BINARY SEARCH TREE ITERATOR
     * Forward and reverse iterator through a BST
     *********************************************************/
    template <typename T>
    class BST <T> ::iterator
    {
        friend class ::TestBST; // give unit tests access to the privates
        friend class ::TestMap;
        friend class ::TestSet;

        template <class KK, class VV>
        friend class map;

        template <class TT>
        friend class set;
    public:
        // constructors and assignment
        iterator(BNode* p = nullptr)
        {
            pNode = p;
        }
        iterator(const iterator& rhs)
        {
            pNode = rhs.pNode;
        }
        iterator& operator = (const iterator& rhs)
        {
            if (this != &rhs)
            {
                pNode = rhs.pNode;
            }

            return *this;
        }

        // compare
        bool operator == (const iterator& rhs) const
        {
            return pNode == rhs.pNode;
        }
        bool operator != (const iterator& rhs) const
        {
            return pNode != rhs.pNode;
        }

        // de-reference. Cannot change because it will invalidate the BST
        const T& operator * () const
        {
            assert(pNode != nullptr);
            return pNode->data;
        }

        // increment and decrement
        iterator& operator ++ ();
        iterator   operator ++ (int postfix)
        {
            iterator temp(*this);
            ++(*this);
            return temp;
        }
        iterator& operator -- ();
        iterator   operator -- (int postfix)
        {
            iterator temp(*this);
            --(*this);
            return temp;
        }

        // must give friend status to remove so it can call getNode() from it
        friend BST <T> ::iterator BST <T> ::erase(iterator& it);

    private:

        // the node
        BNode* pNode;
    };


    /*********************************************
     *********************************************
     *********************************************
     ******************** BST ********************
     *********************************************
     *********************************************
     *********************************************/


     /*********************************************
      * BST :: DEFAULT CONSTRUCTOR
      ********************************************/
    template <typename T>
    BST <T> ::BST()
    {
        // ---------- (Michael Code to Complete) ----------
        root = nullptr;
        numElements = 0;
    }

    /*********************************************
     * BST :: COPY CONSTRUCTOR
     * Copy one tree to another
     ********************************************/
    template <typename T>
    BST <T> ::BST(const BST<T>& rhs)
    {
        // ---------- (James Code to Complete) ----------
        numElements = 99;
        root = new BNode;
    }

    /*********************************************
     * BST :: MOVE CONSTRUCTOR
     * Move one tree to another
     ********************************************/
    template <typename T>
    BST <T> ::BST(BST <T>&& rhs)
    {
        // ---------- (James Code to Complete) ----------
        numElements = 99;
        root = new BNode;
    }

    /*********************************************
     * BST :: INITIALIZER LIST CONSTRUCTOR
     * Create a BST from an initializer list
     ********************************************/
    template <typename T>
    BST <T> ::BST(const std::initializer_list<T>& il)
    {
        // ---------- (James Code to Complete) ----------
        numElements = 99;
        root = new BNode;
    }

    /*********************************************
     * BST :: DESTRUCTOR
     ********************************************/
    template <typename T>
    BST <T> :: ~BST()
    {
        // ---------- (Michael Code to Complete) ----------
        clear();
    }


    /*********************************************
     * BST :: ASSIGNMENT OPERATOR
     * Copy one tree to another
     ********************************************/
    template <typename T>
    BST <T>& BST <T> :: operator = (const BST <T>& rhs)
    {
        // ---------- (James Code to Complete) ----------
        return *this;
    }

    /*********************************************
     * BST :: ASSIGNMENT OPERATOR with INITIALIZATION LIST
     * Copy nodes onto a BTree
     ********************************************/
    template <typename T>
    BST <T>& BST <T> :: operator = (const std::initializer_list<T>& il)
    {
        // ---------- (James Code to Complete) ----------

        return *this;
    }

    /*********************************************
     * BST :: ASSIGN-MOVE OPERATOR
     * Move one tree to another
     ********************************************/
    template <typename T>
    BST <T>& BST <T> :: operator = (BST <T>&& rhs)
    {
        // ---------- (James Code to Complete) ----------

        return *this;
    }

    /*********************************************
     * BST :: SWAP
     * Swap two trees
     ********************************************/
    template <typename T>
    void BST <T> ::swap(BST <T>& rhs)
    {
        // ---------- (James Code to Complete) ----------

    }

    /*****************************************************
     * BST :: INSERT
     * Insert a node at a given location in the tree
     ****************************************************/

     // ---------- (Michael Code to Complete) ----------
    template <typename T>
    std::pair<typename BST <T> ::iterator, bool> BST <T> ::insert(const T& t, bool keepUnique)
    {
        // empty tree
        if (root == nullptr)
        {
            root = new BNode(t);
            numElements = 1;
            return std::pair<iterator, bool>(iterator(root), true);
        }

        BNode* pCur = root;
        BNode* pPar = nullptr;
        bool wentLeft = false;  // <--- remember last direction

        if (keepUnique)
        {
            while (pCur != nullptr)
            {
                pPar = pCur;

                // must check equality first for keepUnique tests
                if (t == pCur->data)
                    return std::pair<iterator, bool>(iterator(pCur), false);

                wentLeft = (t < pCur->data);       // <--- ONE < per level
                pCur = wentLeft ? pCur->pLeft : pCur->pRight;
            }
        }
        else
        {
            while (pCur != nullptr)
            {
                pPar = pCur;

                wentLeft = (t < pCur->data);       // <--- ONE < per level
                pCur = wentLeft ? pCur->pLeft : pCur->pRight; // duplicates go right
            }
        }

        BNode* pNew = new BNode(t);
        pNew->pParent = pPar;

        // attach WITHOUT another <
        if (wentLeft)
            pPar->pLeft = pNew;
        else
            pPar->pRight = pNew;

        ++numElements;
        return std::pair<iterator, bool>(iterator(pNew), true);
    }
    // ---------- (Michael Code to Complete) ----------
    template <typename T>
    std::pair<typename BST <T> ::iterator, bool> BST <T> ::insert(T&& t, bool keepUnique)
    {
        // empty tree
        if (root == nullptr)
        {
            root = new BNode(std::move(t));
            numElements = 1;
            return std::pair<iterator, bool>(iterator(root), true);
        }

        BNode* pCur = root;
        BNode* pPar = nullptr;
        bool wentLeft = false;  // <--- remember last direction

        if (keepUnique)
        {
            while (pCur != nullptr)
            {
                pPar = pCur;

                if (t == pCur->data)
                    return std::pair<iterator, bool>(iterator(pCur), false);

                wentLeft = (t < pCur->data);       // <--- ONE < per level
                pCur = wentLeft ? pCur->pLeft : pCur->pRight;
            }
        }
        else
        {
            while (pCur != nullptr)
            {
                pPar = pCur;

                wentLeft = (t < pCur->data);       // <--- ONE < per level
                pCur = wentLeft ? pCur->pLeft : pCur->pRight;
            }
        }

        BNode* pNew = new BNode(std::move(t));
        pNew->pParent = pPar;

        // attach WITHOUT another <
        if (wentLeft)
            pPar->pLeft = pNew;
        else
            pPar->pRight = pNew;

        ++numElements;
        return std::pair<iterator, bool>(iterator(pNew), true);
    }

    /*************************************************
     * BST :: ERASE
     * Remove a given node as specified by the iterator
     ************************************************/
    template <typename T>
    typename BST <T> ::iterator BST <T> ::erase(iterator& it)
    {
        // ---------- (James Code to Complete) ----------
        return end();
    }

    /*****************************************************
     * BST :: CLEAR
     * Removes all the BNodes from a tree
     ****************************************************/
    template <typename T>
    void BST <T> ::clear() noexcept
    {
       deleteBinaryTree(root);
       numElements = 0;
    }

    /*****************************************************
     * BST :: DELETE BINARY TREE
     * Core, recursive helper for CLEAR
     ****************************************************/
    template <typename T>
    void BST<T>::deleteBinaryTree(BNode*& pNode) noexcept
    {
       if (pNode == nullptr)
          return;

       deleteBinaryTree(pNode->pLeft);
       deleteBinaryTree(pNode->pRight);

       delete pNode;
       pNode = nullptr;
    }

    /*****************************************************
     * BST :: BEGIN
     * Return the first node (left-most) in a binary search tree
     ****************************************************/
    template <typename T>
    typename BST <T> ::iterator custom::BST <T> ::begin() const noexcept
    {
        // Empty tree
        if (root == nullptr)
           return end();
        
        // Start at root, walk pLeft till null
        BNode* pCur = root;
        while (pCur->pLeft != nullptr)
           pCur = pCur->pLeft;
        return iterator(pCur);
    }


    /****************************************************
     * BST :: FIND
     * Return the node corresponding to a given value
     ****************************************************/
    template <typename T>
    typename BST <T> ::iterator BST<T> ::find(const T& t)
    {
        BNode* pCur = root;
        while (pCur != nullptr)
        {
           if (t == pCur->data) // found it
              return iterator(pCur);
           else if (t < pCur->data) // go left
              pCur = pCur->pLeft;
           else // go right
              pCur = pCur->pRight;
        }
        return end();
    }

    /******************************************************
     ******************************************************
     ******************************************************
     *********************** B NODE ***********************
     ******************************************************
     ******************************************************
     ******************************************************/


     /******************************************************
      * BINARY NODE :: ADD LEFT
      * Add a node to the left of the current node
      ******************************************************/
    template <typename T>
    void BST <T> ::BNode::addLeft(BNode* pNode)
    {
        // ---------- (Michael Code to Complete) ----------
        pLeft = pNode;
        if (pNode)
            pNode->pParent = this;
    }

    /******************************************************
     * BINARY NODE :: ADD RIGHT
     * Add a node to the right of the current node
     ******************************************************/
    template <typename T>
    void BST <T> ::BNode::addRight(BNode* pNode)
    {
        // ---------- (Michael Code to Complete) ----------
        pRight = pNode;
        if (pNode)
            pNode->pParent = this;
    }

    /******************************************************
     * BINARY NODE :: ADD LEFT
     * Add a node to the left of the current node
     ******************************************************/
    template <typename T>
    void BST<T> ::BNode::addLeft(const T& t)
    {
        // ---------- (Michael Code to Complete) ----------
        addLeft(new BNode(t));
    }

    /******************************************************
     * BINARY NODE :: ADD LEFT
     * Add a node to the left of the current node
     ******************************************************/
    template <typename T>
    void BST<T> ::BNode::addLeft(T&& t)
    {
        // ---------- (Michael Code to Complete) ----------
        addLeft(new BNode(std::move(t)));
    }

    /******************************************************
     * BINARY NODE :: ADD RIGHT
     * Add a node to the right of the current node
     ******************************************************/
    template <typename T>
    void BST <T> ::BNode::addRight(const T& t)
    {
        // ---------- (Michael Code to Complete) ----------
        addRight(new BNode(t));
    }

    /******************************************************
     * BINARY NODE :: ADD RIGHT
     * Add a node to the right of the current node
     ******************************************************/
    template <typename T>
    void BST <T> ::BNode::addRight(T&& t)
    {
        // ---------- (Michael Code to Complete) ----------
        addRight(new BNode(std::move(t)));
    }



    /*************************************************
     *************************************************
     *************************************************
     ****************** ITERATOR *********************
     *************************************************
     *************************************************
     *************************************************/

     /**************************************************
      * BST ITERATOR :: INCREMENT PREFIX
      * advance by one
      *************************************************/
    template <typename T>
    typename BST <T> ::iterator& BST <T> ::iterator :: operator ++ ()
    {
        // ---------- (Michael Code to Complete) ----------
        if (pNode == nullptr)
            return *this; // ++end() stays end()

        // if there is a right subtree, next is left-most of it
        if (pNode->pRight != nullptr)
        {
            pNode = pNode->pRight;
            while (pNode->pLeft != nullptr)
                pNode = pNode->pLeft;
            return *this;
        }

        // otherwise, climb until we come from a left child
        auto pCur = pNode;
        auto pPar = pNode->pParent;
        while (pPar != nullptr && pCur == pPar->pRight)
        {
            pCur = pPar;
            pPar = pPar->pParent;
        }
        pNode = pPar; // may be nullptr (end)
        return *this;
    }

    /**************************************************
     * BST ITERATOR :: DECREMENT PREFIX
     * advance by one
     *************************************************/
    template <typename T>
    typename BST <T> ::iterator& BST <T> ::iterator :: operator -- ()
    {
        // ---------- (Michael Code to Complete) ----------
        if (pNode == nullptr)
            return *this; // tests expect --end() stays end()

        // if there is a left subtree, prev is right-most of it
        if (pNode->pLeft != nullptr)
        {
            pNode = pNode->pLeft;
            while (pNode->pRight != nullptr)
                pNode = pNode->pRight;
            return *this;
        }

        // otherwise, climb until we come from a right child
        auto pCur = pNode;
        auto pPar = pNode->pParent;
        while (pPar != nullptr && pCur == pPar->pLeft)
        {
            pCur = pPar;
            pPar = pPar->pParent;
        }
        pNode = pPar; // may be nullptr (end)
        return *this;
    }


} // namespace custom