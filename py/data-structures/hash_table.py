class HashTable:
    def __init__(self):
        self.initial_size = 1543 # credits: https://planetmath.org/goodhashtableprimes
        self.table = [None for _ in range(self.initial_size+1)]
        self.free_slots = len(self.table)

    def __repr__(self):
        return str({e[0]:e[1] for e in self.table if e != None })
    

    def add(self,key,value):
        result = self.__search(key)
        self.table[result[0]] = (key,value)
        # if this was a new entry , decreemnt free slots
        if not result[1]:
            self.free_slots -= 1


        # resize the hash table when only 1/3 of the capcity is free
        if self.free_slots < 0.3 * len(self.table):
            self.__resize()
     
    def remove(self,key):
        result = self.__search(key)
        if result[1]:
            self.table[result[0]] = None
            self.free_slots += 1
            return
        raise Exception("the key doesn't exist")

    def get(self,key):
        result = self.__search(key)
        if result[1]:
            return result[1][1]
        raise Exception("the key doesn't exist")
    
    def __search(self,key):
        # return the tuple of (true_index,(key,value )) if the key exists otherwise (idx,None)
        # useful for direct manipulation of the table
        idx = hash(key) % len(self.table)
        search_idx = idx
        while self.table[search_idx] != None:
            if self.table[search_idx][0] == key:
                return (search_idx,self.table[search_idx])
            search_idx += 1
            search_idx %= len(self.table)
            if search_idx == idx:
                break
        return (search_idx,None)
    
    def __resize(self):
        new_table = [None for _ in range(len(self.table) * 2)]
        for e in self.table:
            if e:
                new_idx = hash(e[0]) % len(new_table)
                new_table[new_idx] = e
        self.table = new_table
        self.free_slots = len(self.table) * 2
