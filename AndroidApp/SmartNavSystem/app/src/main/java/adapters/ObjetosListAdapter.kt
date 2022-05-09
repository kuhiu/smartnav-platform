package adapters

import Entities.Objetos
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.ImageView
import android.widget.TextView
import androidx.cardview.widget.CardView
import androidx.recyclerview.widget.RecyclerView
import com.example.myapplication3.R
import database.ObjetoDao
import database.appDatabase

class ObjetosListAdapter(
    val objDao: ObjetoDao,
    val onItemClick: (Int) -> Boolean, val onButtonDelClick: (Int) -> Boolean) : RecyclerView.Adapter<ObjetosListAdapter.ObjetosHolder>()
{

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ObjetosHolder {
        // Busco el item
        val view = LayoutInflater.from(parent.context).inflate(R.layout.item_objeto,parent,false)
        return(ObjetosListAdapter.ObjetosHolder(view))
    }

    override fun getItemCount(): Int {
        if (objDao.loadAllObjects()?.size == null)
            return 0
        else
            return (objDao?.loadAllObjects()?.size!!)
    }

    override fun onBindViewHolder(holder: ObjetosHolder, position: Int) {

        holder.setName((objDao.loadAllObjects() as MutableList<Objetos> )[position].nombre)
        holder.setPic((objDao.loadAllObjects() as MutableList<Objetos> )[position].obj_img)

        holder.getCardLayout().setOnClickListener() {
            onItemClick(position)
        }

        holder.getButton().setOnClickListener {
            onButtonDelClick(position)
        }
    }

    // Tiene las instancias del xml del item findviewid de los items
    // Todas las interacciones con el item van aca
    class ObjetosHolder (v: View) : RecyclerView.ViewHolder(v) {
        private var view: View

        init {
            this.view = v
        }

        fun setName(name: String) {
            val txt: TextView = view.findViewById(R.id.txt_name_item)
            txt.text = name
        }

        fun setPic(src: Int) {
            val pic: ImageView = view.findViewById(R.id.img_item)
            pic.setImageResource(src)
        }

        fun getCardLayout (): CardView {
            return view.findViewById(R.id.card_package_item)
        }

        fun getButton (): Button {
            return view.findViewById(R.id.btn_remove)
        }

    }

}