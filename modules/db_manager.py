from db import Db

class Bd_manager() :
    def __init__(self) -> None:
        self.db = Db()

    def update_db(self):
        if self.db.count_entrie_row() == 0:
            with open("lines.txt", "r") as r:
                ligne_texte = r.readlines()
                for line in ligne_texte:
                    x = line.split(',')
                    for c in range(len(x)):
                        table = x
                self.db.insert_entries((table[0], table[1], table[2], table[3], table[4], table[5], table[6], table[7])) 
                print("Mise à jour de la base de données terminée avec succès!")
            count = self.db.count_entrie_row()
            r.close()
            self.db.cur.execute("INSERT INTO row_count VALUES (?)", (count))
        else:
            with open("lines.txt", "r") as r:
                ligne_texte = r.readlines()
                if self.db.count_entrie_row < len(ligne_texte):
                    for line in ligne_texte:
                        x = line.split(',')
                        for c in range(len(x)):
                            table = x
                        req_check_if_exist = "SELECT * FROM entries WHERE id = :id"
                        if (self.db.cur.execute(req_check_if_exist, {"id":table[0]})):
                            pass
                        else:
                            self.db.insert_entries((table[0], table[1], table[2], table[3], table[4], table[5], table[6], table[7])) 
                            print("Mise à jour de la base de données terminée avec succès!")
                else:
                    print("La base de données est déjà à jour")
            count = self.db.count_entrie_row()
            r.close()
            self.db.update_row_count(count)