public class binaryTree<T>{

	private class Node<T>{
		private T elem;
		private Node<T> left;
		private Node<T> right;

		public Node(T e){
			elem = e;
		}

		public void setElem(T e){
			elem = e;
		}

		public T getElem(){
			return elem;
		}

		public Node<T> getLeft(){
			return left;
		}

		public Node<T> getRight(){
			return right;
		}

		public void addNode(T e){
			if(elem == e){
				return;
			}

			if(elem > e){
				left.setElem(e);
			}else{
				right.setElem(e);
			}
		}



	}
	//end node.. star binaryTree

	Node<T> root;
	Node<T> tempNode;

	public binaryTree(T elem){
		root = new Node<T>(elem);
		tempNode = root;
	}

	public void add(T elem){
		if(tempNode == null){
			tempNode.addNode(elem);
		}else{
			tempNode = tempNode.getRight();
			tempNode = tempNode.getLeft();
			add(elem);
		}
	}




}