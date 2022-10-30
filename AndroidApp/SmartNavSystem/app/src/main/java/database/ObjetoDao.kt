package database

import Entities.Objetos
import androidx.room.*


@Dao
public interface ObjetoDao {

    @Query("SELECT * FROM Objetos ORDER BY nombre")
    fun loadAllObjects(): MutableList<Objetos?>?

    @Insert(onConflict = OnConflictStrategy.IGNORE)
    fun insertObject(user: Objetos?) : Long

    @Update
    fun updateObject(user: Objetos?)

    @Delete
    fun deleteObject(user: Objetos?)

    @Query("SELECT * FROM Objetos WHERE nombre = :nombre")
    fun loadObjectByName(nombre: String): Objetos?

    //@Query("SELECT * FROM Objetos WHERE POSITION(:position) ")
    //fun searchObjectByPosition(position: String): Objetos?

}