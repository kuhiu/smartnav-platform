/*package database

import Entities.Objetos
import androidx.room.*

@Dao
public interface MyObjectInterface {

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

}*/