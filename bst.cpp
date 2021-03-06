#include "bst.h"



/***************************************************************************************

Funcion de abstracción:

fA:	repr -> Arbol Binario de Búsqueda
	{raiz} -> Raíz del Árbol
	
	La estructura {raiz} de tipo nodo junto al resto de nodos enlazados constituyen el BST
	

Invariante de la Representación:
	Dado dos nodos n y m debe cumplirse que:
	- n.label != m.label
	- n.label > n->left.label  y  n.label < n->right.label

********************************************************************************************/



bool nodo<T>::hijo_izq() const{
if(parent->left==*this)	
	return true;
else return false;
}
		





int nodo<T>::size(const nodo<T> *n) const {
	if(n!=0)
		return 1+size(n->left)+size(n->right);
}





nodo<T> & nodo<T>::operator=(const nodo<T> &n){
		label=n.label;
		parent=n.parent;
		left=n.left;
		right=n.right;
	}
	


	
nodo<T> & BST<U>::private_find(const T &dato) {
	bool encontrado=false;
	bool existe=true;
	nodo<T> *aux=&raiz;
	
	while(!encontrado  &&  existe)
	{
		if(aux.label==dato)
			encontrado=true;
		else
			if(dato<n.label)
				if(n->left==NULL)
					existe=false;
				else
					n=n->left;
			else
				if(n->right==NULL)
					existe=false;
				else
					n=n->right;
	}
	
	if(!existe)
		aux=NULL;
	return *aux;		
}





void borrar_nodos(nodo<T> &n){
	if(n.left!=0)
		borrar_nodos(n->left);
	if(n.right!=0)
		borrar_nodos(n->right);
	delete n;
}




///////////////////////////////////////////////////////////////////////////////////





BST<U>::BST<U>(const T &e){
	raiz.label=e;
	
	parent=NULL;
	left=NULL;
	right=NULL;
}



bool BST<U>::insert(const T &dato){
	bool repedito=false;
	nodo<T> *aux=&raiz;
	nodo<T> *padre;
	
	while(!repetido  &&  aux!=NULL)
	{
		if(aux->label==dato)
			repetido=true;
		else
			if(dato<aux->label)
			{
				padre=aux;
				aux=aux->left;
			}
			else
			{
				padre=aux;
				aux=aux->right;
			}
	}
	if(!repetido)
		if(padre->label>dato)
		{
			padre->left=new nodo<T>;
			padre->left->parent=padre;
			padre=padre->left;
			padre->left=NULL;
			padre->right=NULL;
		}
		else
		{
			padre->right=new nodo<T>;
			padre->right->parent=padre;
			padre=padre->right;
			padre->left=NULL;
			padre->right=NULL;
		}
	return repetido;
}
	
	

bool BST<U>::find(const T &dato){
	nodo<T> *aux=private_find(dato);
	if(aux==NULL)
		return false;
	else
		return true;
}




bool BST<U>::erase(const T &dato){
	nodo<T> *aux=private_find(dato);
	nodo<T> *aux2=aux;
	
	if(aux==NULL)
		return false;
	
	if(aux->left==NULL  &&  aux->right==NULL)	//ES HOJA
	{
		if((*aux).hijo_izquierdo)
		{
			aux=aux->parent;
			delete aux->left;
			aux->left=NULL;
		}
		else	// Si es hijo derecho
		{
			aux=aux->parent;
			delete aux->right;
			aux->right=NULL;
		}
	}
	else
		if(aux->left!=NULL  &&  aux->right==NULL)	//si solo tiene hijo izq
		{
			aux=aux->parent;
			aux->left=aux->left->left;
			aux->left->parent=aux;
		}
		else
			if(aux->left==NULL  &&  aux->right!=NULL)	//Si solo tiene hijo der
			{
				aux=aux->parent;
				aux->right=aux->right->right;
				aux->right->parent=aux;
			}
			else
				if(aux->left!=NULL  &&  aux->right!=NULL)	//si tiene dos hijos cambio el nodo por el hijo mas a la derecha de su hijo a la izquierda.
				{
					aux=aux->left;
					if(aux->right!=NULL)	
					{
						while(aux->right!=NULL)
							aux=aux->right;
						aux2->label=aux->label;	//aux2 apuntaba al nodo que queremos borrar
						aux=aux->parent;
						delete aux->right;
						aux->right=NULL;
					}
					else	//si el hijo de la izquierda no tiene ningun hijo a la derecha...
					{
						aux2=aux2->parent;
						aux2->left=aux;
						aux->right=aux->parent->right;
						delete aux->parent;
						aux->parent=aux2;
					}
				}
	return true;
}


int BST<U>::size(){
	return raiz.size();
}


void clear(){
	borrar_nodos(raiz);
}


~BST<U>(){
	borrar_nodos(raiz);
}
	