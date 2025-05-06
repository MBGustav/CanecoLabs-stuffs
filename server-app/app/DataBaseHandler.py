import mysql.connector
import mysql.connector
from mysql.connector import Error
import mysql.connector.cursor

class DataBaseHandler:
    def __init__(self, user, password, database, auto_connect= True):
        self.user:str      = user
        self.password: str = password
        self.database: str = database
        self.connection: mysql.connector.connection.MySQLConnection | None = None

        if auto_connect:
            self.connect()
    
    def get_database(self) -> str:
        return f"{self.database}"
    
    def get_user(self) -> str:
        return f"{self.user}"
    
    def connect(self) -> None:
        try:
            self.connection = mysql.connector.connect(
                user=self.user,
                password=self.password,
                database=self.database,
            )
            print("Connection established successfully.")
        except Error as e:
            print(f"Error connecting to database: {e}")
            exit(e)

    def close_connection(self) -> None:
        if self.connection:
            self.connection.close()
            print("Connection closed.")

    
    def query(self, str_query : str) -> list:
        result_query = list()
        cursor = self.connection.cursor()

        cursor.execute(str_query)

        for row in cursor:
            result_query.append(row)
        
        cursor.close() #should I ?

        return result_query

    def insert(self, s_query: str) -> int:

        o_cursor = self.connection.cursor()

        o_cursor.execute(s_query)
        i_inserted_row_count = o_cursor.rowcount

        # Make sure data is committed to the database
        self.connection.commit()

        return i_inserted_row_count

    def delete(self, str_query : str) -> int :
        o_cursor = self.connection.cursor()

        o_cursor.execute(str_query)
        i_deleted_row_count = o_cursor.rowcount

        # Make sure data is committed to the database
        self.connection.commit()

        return i_deleted_row_count

    def get_tables(self) -> list:
        tables = []
        query = "SHOW TABLES"
        cursor = self.connection.cursor()

        cursor.execute(query)

        for table in cursor:
            tables.append(table[0])  # Extract table name from tuple

        cursor.close()

        return tables


class UserQueryHandler: 

#student_id, 
#student_cardId, 
#student_hierarchy, 
#student_name, 
#student_course
    def __init__(self, db_handler: DataBaseHandler):
        self.db_handler = db_handler

    def get_user_by_cardId(self, user_id: int) -> dict:
        query = f"SELECT student_id FROM STUDENT_DATA WHERE student_cardId = {user_id}"
        result = self.db_handler.query(query)
        if result:
            columns = [desc[0] for desc in self.db_handler.connection.cursor().description]
            return dict(zip(columns, result[0]))
        return {}

    def add_user(self, id_RA     : str, cardId : str,
                       hierarchy : str, name   : str,
                       course    : str) -> int:
        query = f"INSERT INTO STUDENT_DATA      \
        (student_id, student_cardId,            \
         student_hierarchy, student_name,       \
         student_course)                        \
            VALUES                              \
        ('{id_RA}', '{cardId}',                 \
        '{hierarchy}', '{name}', '{course}')"
        return self.db_handler.insert(query)

    def delete_user_by_id(self, user_id: int) -> int:
        query = f"DELETE FROM STUDENT_DATA WHERE id = {user_id}"
        return self.db_handler.delete(query)

    def list_all_students(self) -> list:
        query = "SELECT student_id, student_name, student_course  FROM STUDENT_DATA"
        result = self.db_handler.query(query)
        result = []
        if result:
            columns = [desc[0] for desc in self.db_handler.connection.cursor().description]
            for row in result:
                result.append(dict(zip(columns, row)))
        return result