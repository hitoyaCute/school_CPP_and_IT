
class NODE:
    def __init__ (self, data):
        self.data = data
        self.file_addr = None
        self.child_low = -1
        self.child_high = -1
    
    def binary_decide(self, target: int) -> int:
        # return the address of the chossen child                       
        if self.data < target:
            return 1
        return 0
    def read(self, index) -> int:
        if index:
            return self.child_high
        return self.child_low
    def write(self, index, data):
        if index:
            self.child_high = data
            return
        self.child_low = data

class tree:
    def __init__(self):
        self.nodes : list[NODE] = []

    def show_tree(self):
        print("{",end="")
        for i,node in enumerate(self.nodes):
              print(f"node_{i}: "+
                    "{low: "+f"{node.child_low}"+
                      f",high: {node.child_high},data: {node.data}"+"}, ",end="")
        print("}")

    def find_node(self, target:int) -> int:
        if len(self.nodes) == 0:
            raise ValueError("\"You will never find a food from a empty freezer\" - meu")
        current_node = 0

        while True:
            print(f"route: {current_node}")
            if self.nodes[current_node].data == target:
                return current_node
            else:
                working_node = self.nodes[current_node]
                current_node = working_node.read(working_node.binary_decide(target))
                if current_node == -1 or current_node > len(self.nodes):
                    self.show_tree()
                    raise Exception(f"something went wrong last_node:{current_node}, tree_size:{len(self.nodes)}, node_dat:{working_node.data}")

    def add_node(self, data:int) -> NODE:
        node = NODE(data)
        if len(self.nodes) == 0:
            self.nodes.append(node)
            return node
        else:
            
            child_node_ref = self.nodes[0].binary_decide(data)
            child_node_addr = self.nodes[0].read(child_node_ref)
            child_node_worker = 0
            
            while True:
                if child_node_addr != -1:
                    child_node_worker = child_node_addr
                    child_node_ref = self.nodes[child_node_worker].binary_decide(data)
                else:
                    self.nodes[child_node_worker].write(child_node_ref, len(self.nodes))
                    self.nodes.append(node)

                    return node
                child_node_addr = self.nodes[child_node_worker].read(child_node_ref)








if __name__ == "__main__":
    bin_tree = tree()

    d = [8,3,10,1,6,14,4,7,13]
    for i in d:
        bin_tree.add_node(i)

    num = bin_tree.find_node(14)
    print(f"node num: {num}")
    bin_tree.show_tree()
