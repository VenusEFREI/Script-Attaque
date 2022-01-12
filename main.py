import sys
from db_manager import Db_manager
from payloads import Payload

if __name__ == "__main__":
    if sys.argv[1]  == "update":
        assert len(sys.argv) > 2 and sys.argv[2] in ("exploits", "payloads"), """
        le laucher requiert une opération : exploits ou payloads"""
        if sys.argv[2] == "exploits":
            Update_exploits = Db_manager()
            Update_exploits.update_db()
        elif sys.argv[2] == "payloads":
            Update_payloads = Payload()
            Update_payloads.create_directory()
    else:
        print("Option non prise en charge!")