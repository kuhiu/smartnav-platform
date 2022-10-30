package Fragments

import Entities.Objetos
import adapters.ObjetosListAdapter
import android.app.AlertDialog
import android.app.Dialog
import android.content.DialogInterface
import android.graphics.Color
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.EditText
import androidx.fragment.app.Fragment
import androidx.navigation.findNavController
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.myapplication3.R
import com.google.android.material.floatingactionbutton.FloatingActionButton
import com.google.android.material.snackbar.Snackbar
import com.google.firebase.database.collection.LLRBNode
import database.ObjetoDao
import database.appDatabase


class listFragment : Fragment() {

    private lateinit var v: View

    private lateinit var recObjetos: RecyclerView
    private lateinit var linearLayoutManager: LinearLayoutManager

    // Instancio el adaptador
    private lateinit var MyAdaptadorDeObjetos: ObjetosListAdapter

    // Botones para agregar y quitar de la lista de objetos
    private lateinit var btn_add: FloatingActionButton
    private lateinit var btn_remove: Button

    // Edit text para guardar datos sobre el objeto a agregar
    private lateinit var edt_txt_name: EditText

    // Base de datos de objetos
    private var db: appDatabase? = null
    private var objDao: ObjetoDao? = null

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View {
        // Inflate the layout for this fragment
        v = inflater.inflate(R.layout.fragment_list, container, false)
        recObjetos = v.findViewById(R.id.rec_Objetos)
        btn_add = v.findViewById(R.id.float_btn_add)
        btn_remove = inflater.inflate(R.layout.item_objeto, container, false).findViewById(R.id.btn_remove)
        return v
    }

    override fun onStart() {
        super.onStart()

        db = appDatabase.getAppDataBase(v.context)
        objDao = db?.objDao()

        // Inserto algunos objetos si no existen en la base de datos
        objDao?.insertObject(Objetos("tomate", "gs://navsys-e2185.appspot.com/tomate/", R.drawable.tomate))
        objDao?.insertObject(Objetos("persona", "gs://navsys-e2185.appspot.com/persona/", R.drawable.personas))
        objDao?.insertObject(Objetos("caja", "gs://navsys-e2185.appspot.com/caja/", R.drawable.caja))

        recObjetos.setHasFixedSize(true)                        // Acomoda el tamaño en la ventana
        linearLayoutManager = LinearLayoutManager(context)
        recObjetos.layoutManager = linearLayoutManager

        MyAdaptadorDeObjetos = objDao?.let { ObjetosListAdapter( it, { x -> onItemClick(x) }) { y -> onButtonDelClick(y) } }!!
        recObjetos.adapter = MyAdaptadorDeObjetos

        btn_add.setOnClickListener {
            Log.d("Test", "Entree btn_add" + "\n")
            abrir_dialogo()
        }
    }

    private fun abrir_dialogo(){
        val builder = AlertDialog.Builder(context)
        val inflaterr = requireActivity().layoutInflater
        lateinit var dialog : Dialog
        val v2 = inflaterr.inflate(R.layout.dialog, null)
        edt_txt_name = v2.findViewById(R.id.name)

        builder.setView(v2)
            // Add action buttons
            .setPositiveButton("Guardar", DialogInterface.OnClickListener() { dialog: DialogInterface, id: Int ->
                val OnConflict1 = objDao?.insertObject(Objetos(edt_txt_name.text.toString(), "gs://navsys-e2185.appspot.com/tomate/", R.drawable.tomate))
                if (OnConflict1 == (-1).toLong() )
                    Snackbar.make(v, "El objeto ya existe", Snackbar.LENGTH_SHORT).show()
                else
                    Snackbar.make(v, "Objeto agregado con exito", Snackbar.LENGTH_SHORT).show()
                MyAdaptadorDeObjetos.notifyDataSetChanged()
            })
            .setNegativeButton("Cancelar", DialogInterface.OnClickListener { dialog, id ->
                // getDialog().cancel()
            })

        dialog = builder.create()
        dialog.show()
        dialog.getButton(AlertDialog.BUTTON_NEGATIVE).setTextColor(Color.BLACK);
        dialog.getButton(AlertDialog.BUTTON_POSITIVE).setTextColor(Color.BLACK);
    }

    private fun onItemClick (position : Int ) : Boolean {
        val action3 = listFragmentDirections.actionListFragmentToListDetalleFragment( (objDao!!.loadAllObjects() as MutableList<Objetos> )[position] )
        v.findNavController().navigate(action3)
        return true
    }

    private fun onButtonDelClick (position : Int ) : Boolean {
        //Log.d("Test", "El objeto a eliminar sera el: " + objDao?.searchObjectByPosition(position).toString() + "\n")
        objDao?.deleteObject((objDao!!.loadAllObjects() as MutableList<Objetos> )[position])
        MyAdaptadorDeObjetos.notifyDataSetChanged()
        return true
    }

}



